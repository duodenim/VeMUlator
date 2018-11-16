mod cpu;
mod opcodes;

use cpu::CPU;

use std::io::Read;
use std::env;
use std::fs::File;

fn main() {
    //Get game file to open
    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: emulator path/to/game/file.vms");
        std::process::exit(0);
    }

    //Read file into a buffer
    let mut file = File::open(&args[1]).unwrap();
    let metadata = file.metadata().unwrap();

    let mut rom_data = vec![0; metadata.len() as usize];

    file.read(&mut rom_data).unwrap();

    //Create CPU object with loaded ROM
    let mut cpu = CPU::new(rom_data);

    loop {
        cpu.run();
    }

}
