const fs = require('fs');

const dos_chars = ["\u002E", "\u263A", "\u263B", "\u2665", "\u2666", "\u2663", "\u2660", "\u2022", "\u25D8", "\u25CB", "\u25D9", "\u2642", "\u2640", "\u266A", "\u266B", "\u263C", "\u25BA", "\u25C4", "\u2195", "\u203C", "\u00B6", "\u00A7", "\u25AC", "\u21A8", "\u2191", "\u2193", "\u2192", "\u2190", "\u221F", "\u2194", "\u25B2", "\u25BC", "\u0020", "\u0021", "\u0022", "\u0023", "\u0024", "\u0025", "\u0026", "\u0027", "\u0028", "\u0029", "\u002A", "\u002B", "\u002C", "\u002D", "\u002E", "\u002F", "\u0030", "\u0031", "\u0032", "\u0033", "\u0034", "\u0035", "\u0036", "\u0037", "\u0038", "\u0039", "\u003A", "\u003B", "\u003C", "\u003D", "\u003E", "\u003F", "\u0040", "\u0041", "\u0042", "\u0043", "\u0044", "\u0045", "\u0046", "\u0047", "\u0048", "\u0049", "\u004A", "\u004B", "\u004C", "\u004D", "\u004E", "\u004F", "\u0050", "\u0051", "\u0052", "\u0053", "\u0054", "\u0055", "\u0056", "\u0057", "\u0058", "\u0059", "\u005A", "\u005B", "\u005C", "\u005D", "\u005E", "\u005F", "\u0060", "\u0061", "\u0062", "\u0063", "\u0064", "\u0065", "\u0066", "\u0067", "\u0068", "\u0069", "\u006A", "\u006B", "\u006C", "\u006D", "\u006E", "\u006F", "\u0070", "\u0071", "\u0072", "\u0073", "\u0074", "\u0075", "\u0076", "\u0077", "\u0078", "\u0079", "\u007A", "\u007B", "\u007C", "\u007D", "\u007E", "\u2302", "\u00C7", "\u00FC", "\u00E9", "\u00E2", "\u00E4", "\u00E0", "\u00E5", "\u00E7", "\u00EA", "\u00EB", "\u00E8", "\u00EF", "\u00EE", "\u00EC", "\u00C4", "\u00C5", "\u00C9", "\u00E6", "\u00C6", "\u00F4", "\u00F6", "\u00F2", "\u00FB", "\u00F9", "\u00FF", "\u00D6", "\u00DC", "\u00A2", "\u00A3", "\u00A5", "\u20A7", "\u0192", "\u00E1", "\u00ED", "\u00F3", "\u00FA", "\u00F1", "\u00D1", "\u00AA", "\u00BA", "\u00BF", "\u2310", "\u00AC", "\u00BD", "\u00BC", "\u00A1", "\u00AB", "\u00BB", "\u2591", "\u2592", "\u2593", "\u2502", "\u2524", "\u2561", "\u2562", "\u2556", "\u2555", "\u2563", "\u2551", "\u2557", "\u255D", "\u255C", "\u255B", "\u2510", "\u2514", "\u2534", "\u252C", "\u251C", "\u2500", "\u253C", "\u255E", "\u255F", "\u255A", "\u2554", "\u2569", "\u2566", "\u2560", "\u2550", "\u256C", "\u2567", "\u2568", "\u2564", "\u2565", "\u2559", "\u2558", "\u2552", "\u2553", "\u256B", "\u256A", "\u2518", "\u250C", "\u2588", "\u2584", "\u258C", "\u2590", "\u2580", "\u03B1", "\u00DF", "\u0393", "\u03C0", "\u03A3", "\u03C3", "\u00B5", "\u03C4", "\u03A6", "\u0398", "\u03A9", "\u03B4", "\u221E", "\u03C6", "\u03B5", "\u2229", "\u2261", "\u00B1", "\u2265", "\u2264", "\u2320", "\u2321", "\u00F7", "\u2248", "\u00B0", "\u2022", "\u00B7", "\u221A", "\u207F", "\u00B2", "\u25A0", "\u00A0"];

exports.create_mod = async function create_mod(input_elf, out_offset, symbol_addrs = {}) {
	/** @type{Buffer} */
	let buf = await new Promise((resolve, reject) => fs.readFile(input_elf, (err, buffer) => {
		if(err) reject(err);
		resolve(buffer);
	}));
	//if(buf[16] != 1) throw new Error("Not a relocatable elf file");
	let shoff = buf.readUInt32LE(32);
	let shnum = buf.readUInt16LE(48);
	let shstrndx = buf.readUInt16LE(50);
	//console.log(shoff + ", " + shnum);
	let sections = [];
	let buffer_size_needed = 0;
	for(let i = 0; i < shnum; i++) {
		let base = shoff + (i * 40);
		let section = {
			sh_name: buf.readUInt32LE(base + 0x00),
			sh_type: buf.readUInt32LE(base + 0x04),
			sh_flags: buf.readUInt32LE(base + 0x08),
			sh_addr: buf.readUInt32LE(base + 0x0C),
			sh_offset: buf.readUInt32LE(base + 0x10),
			sh_size: buf.readUInt32LE(base + 0x14),
			sh_link: buf.readUInt32LE(base + 0x18),
			sh_info: buf.readUInt32LE(base + 0x1c),
			sh_addralign: buf.readUInt32LE(base + 0x20),
			sh_entsize: buf.readUInt32LE(base + 0x24)
		};
		if(section.sh_flags & 2) {
			while((buffer_size_needed % section.sh_addralign) != 0) buffer_size_needed++;
			section.buffer_offset = buffer_size_needed;
			buffer_size_needed += section.sh_size;
		}

		//console.log(JSON.stringify(section));
		
		if(section.sh_type != 8 && (section.sh_flags & 2)) {
			/** @type{Buffer} */
			for(let i = 0; i < section.sh_size; i += 4) {
				let str = "";
				for(let j = 0; j < 4; j++) str += dos_chars[buf[section.sh_offset+i+j]];
				//console.log(buf.readUInt32LE(section.sh_offset + i).toString(16).padStart(8, "0") + ", " + str);
			}
		}
		sections.push(section);
	}
	let mod_buffer = Buffer.alloc(buffer_size_needed);
	//console.log(buffer_size_needed);
	for(let section of sections) {
		if(section.sh_type != 8 && (section.sh_flags & 2)) {
			mod_buffer.set(buf.subarray(section.sh_offset, section.sh_offset + section.sh_size), section.buffer_offset);
		}
	}
	let symbols_named = {};
	for(let section of sections) {
		if(section.sh_type == 2) {
			let str_table_offset = sections[section.sh_link].sh_offset;
			section.symbols = [];
			let num_symbols = section.sh_size / 16;
			for(let i = 0; i < num_symbols; i++) {
				let st_off = section.sh_offset + i*16;
				let symbol = {
					st_name: read_str(buf, str_table_offset + buf.readUInt32LE(st_off + 0x00)),
					st_value: buf.readUInt32LE(st_off + 0x04),
					st_size: buf.readUInt32LE(st_off + 0x08),
					st_info: buf[st_off + 0x0C],
					st_other: buf[st_off + 0x0D],
					st_shndx: buf.readUInt16LE(st_off + 0x0E)
				};
				if(sections[symbol.st_shndx]) {
					let abs_base = sections[symbol.st_shndx].buffer_offset;
					if(abs_base !== undefined) {
						symbol.buffer_offset = symbol.st_value + abs_base;
						symbol.abs_addr = symbol.buffer_offset + out_offset
						if(!symbol_addrs[symbol.st_name]) {
							symbol_addrs[symbol.st_name] = symbol.abs_addr;
						}
					}
				}
				//console.log(symbol);
				if(symbol.st_name) symbols_named[symbol.st_name] = symbol;
				section.symbols.push(symbol);
			}
		}
	}
	for(let section of sections) {
		if(section.sh_type == 9) {
			let num_rel = section.sh_size / 8;
			let symbols = sections[section.sh_link].symbols;
			let target_section = sections[section.sh_info];
			//console.log(section.sh_info + ": ");
			for(let i = 0; i < num_rel; i++) {
				let off = section.sh_offset + i*8;
				let r_offset = buf.readUInt32LE(off);
				let r_info = buf.readUInt32LE(off+4);
				let sym = r_info >> 8;
				let type = r_info & 0xFF;
				let type_str = ["R_MIPS_NONE", "R_MIPS_16", "R_MIPS_32", "R_MIPS_REL32", "R_MIPS_26", "R_MIPS_HI16", "R_MIPS_LO16", "R_MIPS_GPREL16", "R_MIPS_LITERAL", "R_MIPS_GOT16", "R_MIPS_PC16", "R_MIPS_CALL16", "R_MIPS_GPREL32"];
				//console.log(r_offset + ", " + type_str[type] + ", " + sym + " (" + (symbols[sym] ? symbols[sym].st_name : "???") + ")");
				let mod_buffer_offset = r_offset + target_section.buffer_offset;
				let abs_addr = symbols[sym].abs_addr;
				//console.log(mod_buffer_offset.toString(16));
				if(!abs_addr) abs_addr = symbol_addrs[symbols[sym].st_name];
				if(!abs_addr) throw new Error("no abs addr for "+ ((symbols[sym] ? symbols[sym].st_name : "???")));
				//console.log(abs_addr.toString(16));
				
				let orig_val = mod_buffer.readUInt32LE(mod_buffer_offset);
				//console.log(orig_val.toString(16));
				switch(type) {
				case 2: // R_MIPS_32
					mod_buffer.writeUInt32LE(abs_addr + orig_val, mod_buffer_offset);
					break;
				case 4: // R_MIPS_26
					mod_buffer.writeInt32LE((orig_val & 0xFC000000) | (0x3FFFFF & (abs_addr >> 2)), mod_buffer_offset);
					break;
				case 5: // R_MIPS_HI16
					let next_r_offset = buf.readUInt32LE(off+8);
					let next_r_info = buf.readUInt32LE(off+12);
					if((next_r_info & 0xFF) != 6) {
						mod_buffer.writeInt32LE((orig_val & 0xFFFF0000) | (((0x8000+abs_addr)|0) >>> 16), mod_buffer_offset);
					} else {
						if((next_r_info >> 8) != sym) throw new Error("R_MIPS_HI16 and following R_MIPS_LO16 have non-matching symbols");
						abs_addr += ((orig_val & 0xFFFF) << 16) | ((mod_buffer.readUInt32LE(next_r_offset + target_section.buffer_offset) << 16) >> 16);
						mod_buffer.writeInt32LE((orig_val & 0xFFFF0000) | (((0x8000+abs_addr)|0) >>> 16), mod_buffer_offset);
					}
					break;
				case 6: // R_MIPS_LO16
					mod_buffer.writeInt32LE((orig_val & 0xFFFF0000) | ((abs_addr + (orig_val & 0xFFFF)) & 0xFFFF), mod_buffer_offset);
					break;
				default:
					throw new Error(`Relocation type ${type}(${type_str[type]}) not implemented`);
				}
			}
		}
	}
	return {
		patches: [
			{addr: out_offset, data: mod_buffer}
		],
		symbols: symbols_named,
	};
}

exports.make_pnach = function make_pnach(mod) {
	let lines = [];
	for(let patch of mod.patches) {
		if(patch.data) {
			for(let i = 0; i < patch.data.length; i += 4) {
				lines.push(`patch=0,EE,${(i+patch.addr).toString(16).toUpperCase()},word,${patch.data.readUInt32LE(i).toString(16).padStart(8, "0").toUpperCase()}`);
			}
		} else if(patch.int_data != undefined) {
			let unsigned = (patch.int_data + 0x100000000) % 0x100000000;
			lines.push(`patch=0,EE,${patch.addr.toString(16).toUpperCase()},word,${unsigned.toString(16).padStart(8, "0").toUpperCase()}`)
		}
	}
	return lines.join("\n") + "\n";
}

exports.patch_file = function patch_file(mod, filename, out_filename, offset) {
	return new Promise((resolve, reject) => {
		fs.readFile(filename, (err, data) => {
			if(err) { reject(err); return; }
			for(let patch of mod.patches) {
				if(patch.data) {
					data.set(patch.data, patch.addr + offset);
				} else if(patch.int_data != undefined) {
					data.writeInt32LE(patch.int_data, patch.addr + offset);
				}
			}
			fs.writeFile(out_filename, data, ()=>{
				resolve();
			})
		})
	});
}

exports.make_c_loader = function make_c_loader(mod) {
	let def_lines = [];
	let code_lines = [];
	let id_ctr = 0;
	def_lines.push("#include <string.h>");
	def_lines.push("");
	code_lines.push("void apply_ntdf_patch(void)");
	code_lines.push("{");
	for(let patch of mod.patches) {
		if(patch.data) {
			let name = "patch_" + id_ctr++;
			def_lines.push("unsigned char " + name + "[] __attribute__((aligned(16))) = {");
			for(let i = 0; i < patch.data.length; i += 16) {
				let line = "\t";
				for(let j = i; (j < patch.data.length && j < i+16); j++) {
					line += "0x"+patch.data[j].toString(16).padStart(2, 0)+", ";
				}
				def_lines.push(line);
			}
			def_lines.push("};");
			def_lines.push("");

			code_lines.push("\tmemcpy((void *)0x" + patch.addr.toString(16) + ", " + name + ", 0x" + patch.data.length.toString(16) + ");");
		} else if(patch.int_data != undefined) {
			code_lines.push("\t*((int*)0x"+patch.addr.toString(16)+") = 0x" + patch.int_data.toString(16) + ";");
		}
	}
	code_lines.push("}");
	
	return def_lines.join("\n") + "\n" + code_lines.join("\n") + "\n";
}

function read_str(buf, offset) {
	let end = offset;
	while(end < buf.length && buf[end] != 0)end++;
	return buf.toString("utf8", offset, end);
}