use std::io::Read;
use std::env;
use std::fs::File;

mod opcodes;

fn main() {
    //Get game file to open
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: disassembler path/to/game/file.vms");
        std::process::exit(0);
    }


    //Read file into a buffer
    let mut file = File::open(&args[1]).unwrap();
    let metadata = file.metadata().unwrap();

    let mut rom_data = vec![0; metadata.len() as usize];

    file.read(&mut rom_data).unwrap();

    let mut pc = 0;

    loop {
        let num_bytes = opcodes::OPCODES_86K[rom_data[pc] as usize].num_bytes;
        let name = opcodes::OPCODES_86K[rom_data[pc] as usize].name;

        print!("0x{:04X}: ", pc);

        for byte_idx in 0..num_bytes {
            print!("0x{:02X} ", rom_data[pc + byte_idx as usize]);
        }

        print!(" - {}\n", name);

        pc += num_bytes as usize;

        if pc >= rom_data.len() {
            break;
        }
    }
}
