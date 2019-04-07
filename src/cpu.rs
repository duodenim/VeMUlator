const ROM_SIZE: usize = 65536;
const RAM_BANK_0_SIZE: usize = 256;
const RAM_BANK_1_SIZE: usize = 256;
const RAM_SFR_SIZE: usize = 256;

const ACC_PTR: u16 = 0x100;
const PSW_PTR: u16 = 0x101;
const B_PTR: u16 = 0x102;
const C_PTR: u16 = 0x103;
const TRL_PTR: u16 = 0x104;
const TRH_PTR: u16 = 0x105;
const SP_PTR: u16 = 0x106;
const P3_PTR: u16 = 0x14C;
const LCD_START_PTR: u16 = 0x180;
const LCD_END_PTR: u16 = 0x1FB;

use opcodes::OPCODES_86K;

const INSTRUCTIONS: [fn(&mut CPU, &[u8]) -> u8; 256]  = [
    CPU::nop, CPU::br_r8, CPU::ld_d9, CPU::ld_d9, //0x00-0x03
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x04-0x07
    CPU::call_a12, CPU::call_a12, CPU::call_a12, CPU::call_a12, //0x08-0x0B
    CPU::call_a12, CPU::call_a12, CPU::call_a12, CPU::call_a12, //0x0C-0x0F
    CPU::unimplemented, CPU::unimplemented, CPU::st_d9, CPU::st_d9, //0x10-0x13
    CPU::st_ri, CPU::st_ri, CPU::st_ri, CPU::st_ri, //0x14-0x17
    CPU::call_a12, CPU::call_a12, CPU::call_a12, CPU::call_a12, //0x18-0x1B
    CPU::call_a12, CPU::call_a12, CPU::call_a12, CPU::call_a12, //0x1C-0x1F
    CPU::unimplemented, CPU::jmpf_a16, CPU::mov_i8_d9, CPU::mov_i8_d9, //0x20-0x23
    CPU::mov_i8_ri, CPU::mov_i8_ri, CPU::mov_i8_ri, CPU::mov_i8_ri, //0x24-0x27
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x28-0x2B
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x2C-0x2F
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x30-0x33
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x34-0x37
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x38-0x3B
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x3C-0x3F
    CPU::unimplemented, CPU::bne_i8_r8, CPU::unimplemented, CPU::unimplemented, //0x40-0x43
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x44-0x47
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x48-0x4B
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x4C-0x4F
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x50-0x53
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x54-0x%7
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x58-0x5B
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x5C-0x5F
    CPU::push_d9, CPU::push_d9, CPU::inc_d9, CPU::inc_d9, //0x60-0x63
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x64-0x67
    CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, //0x68-0x6B
    CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, //0x6C-0x6F
    CPU::pop_d9, CPU::pop_d9, CPU::unimplemented, CPU::unimplemented, //0x70-0x73
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x74-0x77
    CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, //0x78-0x7B
    CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, CPU::bp_d9_b3_r8, //0x7C-0x7F
    CPU::unimplemented, CPU::add_i8, CPU::unimplemented, CPU::unimplemented, //0x80-0x83
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x84-0x87
    CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, //0x88-0x8B
    CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, //0x8C-0x8F
    CPU::bnz_r8, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x90-0x93
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0x94-0x97
    CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, //0x98-0x9B
    CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, CPU::bn_d9_b3_r8, //0x9C-0x9F
    CPU::ret, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xA0-0xA3
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xA4-0xA7
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xA8-0xAB
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xAC-0xAF
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xB0-0xB3
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xB4-0xB7
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xB8-0xBB
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xBC-0xBF
    CPU::unimplemented, CPU::ldc, CPU::unimplemented, CPU::unimplemented, //0xC0-0xC3
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xC4-0xC7
    CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, //0xC8-0xCB
    CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, //0xCC-0xCF
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xD0-0xD3
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xD4-0xD7
    CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, //0xD8-0xDB
    CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, CPU::clr1_d9_b3, //0xDC-0xDF
    CPU::unimplemented, CPU::and_i8, CPU::unimplemented, CPU::unimplemented, //0xE0-0xE3
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xE4-0xE7
    CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, //0xE8-0xEB
    CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, //0xEC-0xEF
    CPU::unimplemented, CPU::unimplemented, CPU::xor_d9, CPU::xor_d9, //0xF0-0xF3
    CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, CPU::unimplemented, //0xF4-0xF7
    CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, //0xF8-0xFB
    CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, CPU::set1_d9_b3, //0xFC-0xFF
];

pub struct CPU {
    rom: Vec<u8>,
    ram_bank0: [u8; RAM_BANK_0_SIZE],
    ram_bank1: [u8; RAM_BANK_1_SIZE],
    ram_sfr: [u8; RAM_SFR_SIZE],
    program_counter: u16
}

impl CPU {
    pub fn new(rom: Vec<u8>) -> CPU {
        assert!(rom.len() <= ROM_SIZE, "ROM is too big!");
        let mut cpu = CPU {
            rom,
            ram_bank0: [0; RAM_BANK_0_SIZE],
            ram_bank1: [0; RAM_BANK_1_SIZE],
            ram_sfr: [0; RAM_SFR_SIZE],
            program_counter: 0
        };

        //Initialize SFRs
        cpu.write_ram_value(SP_PTR, 0x7F);

        cpu
    }

    pub fn run(&mut self) {
        let instr_code = self.rom[self.program_counter as usize];

        let mut instruction = Vec::new();

        for i in 0..OPCODES_86K[instr_code as usize].num_bytes {
            instruction.push(self.rom[self.program_counter as usize + i as usize]);
        }

        //Do program counter adjustment here, which will be overwritten by JMP or CALLs as necessary
        self.program_counter += OPCODES_86K[instr_code as usize].num_bytes as u16;
        INSTRUCTIONS[instr_code as usize](self, &instruction);
    }

    fn read_ram_value(&self, address: u16) -> u8 {
        assert!(address <= 0x1FF, "Address must be less than 512!");

        if address & 0x100 != 0 { //Bit 9 is always used for SFRs
            self.ram_sfr[(address & 0xFF) as usize]
        } else {
            //Assume ram bank 0 for now
            self.ram_bank0[(address & 0xFF) as usize]
        }
    }

    fn write_ram_value(&mut self, address: u16, data: u8) {
        assert!(address <= 0x1FF, "Address must be less than 512!");

        if address & 0x100 != 0 { //BIt 9 is always used for SFRs
            self.ram_sfr[(address & 0xFF) as usize] = data;
        } else {
            //Assume ram bank 0
            self.ram_bank0[(address & 0xFF) as usize] = data;
        }
    }

    fn get_indirect_address(&mut self, register: u8) -> u16 {
        assert!(register <= 3, "Only registers R0 through R3 can be used for indirect addressing!");
        let psw = self.read_ram_value(PSW_PTR);
        let irbk = (psw & 0b00011000) >> 3;
        let mut address = ((4 * irbk) + register) as u16;
        if register == 2 || register == 3 { //R2 and R3 always read from SFRs
            address |= 0x100;
        }

        address
    }

    fn set_carry(&mut self) {
        let psw = self.read_ram_value(PSW_PTR);
        let psw = psw | 0x80;
        self.write_ram_value(PSW_PTR, psw);
    }

    fn clear_carry(&mut self) {
        let psw = self.read_ram_value(PSW_PTR);
        let psw = psw & 0x7F;
        self.write_ram_value(PSW_PTR, psw);
    }

    fn stack_push(&mut self, data: u8) {
        //Increment stack pointer
        let sp = self.read_ram_value(SP_PTR) + 1;

        //Write to new stack pointer value
        self.ram_bank0[sp as usize] = data;
        self.write_ram_value(SP_PTR, sp);
    }

    fn stack_pop(&mut self) -> u8 {
        //Read stack pointer
        let sp = self.read_ram_value(SP_PTR);

        //Read stack
        let ret = self.ram_bank0[sp as usize];
        self.write_ram_value(SP_PTR, sp - 1);

        ret
    }

    fn add_i8(&mut self, instruction: &[u8]) -> u8 {
        let value = instruction[1] as u16;
        let acc = self.read_ram_value(ACC_PTR) as u16;
        let result = value + acc;

        //TODO: CY, AC, and OV checks
        let result = (result & 0xff) as u8;
        self.write_ram_value(ACC_PTR, result);
        1
    }

    fn and_i8(&mut self, instruction: &[u8]) -> u8 {
        let term  = instruction[1];
        let acc = self.read_ram_value(ACC_PTR);
        let acc = acc & term;
        self.write_ram_value(ACC_PTR, acc);
        1
    }

    fn bn_d9_b3_r8(&mut self, instruction: &[u8]) -> u8 {
        let d9_high_bit = ((instruction[0] & 0b00010000) as u16) << 4;
        let d9_low_bits = instruction[1] as u16;
        let address = d9_high_bit | d9_low_bits;
        let bit_address = instruction[0] & 0b00000111;
        let bit_mask = 1 << bit_address;
        let value = self.read_ram_value(address);
        if (value & bit_mask) == 0 {
            let relative_address = instruction[2] as i8;
            self.program_counter = self.program_counter.wrapping_add(relative_address as u16);
        }
        2
    }

    fn bne_i8_r8(&mut self, instruction: &[u8]) -> u8 {
        let compare_value = instruction[1];
        let acc = self.read_ram_value(ACC_PTR);

        if acc < compare_value {
            self.set_carry();
        } else {
            self.clear_carry();
        }

        if acc != compare_value {
            let relative_address = instruction[2] as i8;
            self.program_counter = self.program_counter.wrapping_add(relative_address as u16);
        }

        2
    }

    fn bnz_r8(&mut self, instruction: &[u8]) -> u8 {
        let acc = self.read_ram_value(ACC_PTR);

        if acc != 0 {
            let relative_address = instruction[1] as i8;
            self.program_counter = self.program_counter.wrapping_add(relative_address as u16);
        }

        2
    }

    fn bp_d9_b3_r8(&mut self, instruction: &[u8]) -> u8 {
        let d9_high_bit = ((instruction[0] & 0b00010000) as u16) << 4;
        let d9_low_bits = instruction[1] as u16;
        let address = d9_high_bit | d9_low_bits;
        let bit_address = instruction[0] & 0b00000111;
        let bit_mask = 1 << bit_address;
        let value = self.read_ram_value(address);
        if (value & bit_mask) != 0 {
            let relative_address = instruction[2] as i8;
            self.program_counter = self.program_counter.wrapping_add(relative_address as u16);
        }

        2
    }

    fn br_r8(&mut self, instruction: &[u8]) -> u8 {
        let relative_address = instruction[1] as i8;
        self.program_counter = self.program_counter.wrapping_add(relative_address as u16);
        println!("Branch address is {:X}", self.program_counter);

        2
    }

    fn call_a12(&mut self, instruction: &[u8]) -> u8 {
        let call_address_low = instruction[1] as u16;
        let call_address_mid = ((instruction[0] & 0b00000111) as u16) << 8;
        let call_address_high = ((instruction[0] & 0b00010000) as u16) << 7;
        let current_high_4_bits = self.program_counter & 0xF000;
        let call_address = call_address_low | call_address_mid | call_address_high | current_high_4_bits;

        let save_address_low = (self.program_counter & 0x00FF) as u8;
        let save_address_high = ((self.program_counter & 0xFF00) >> 8) as u8;

        //Save pc onto stack
        self.stack_push(save_address_low);
        self.stack_push(save_address_high);

        //Set program counter to call address
        self.program_counter = call_address;

        2
    }

    fn clr1_d9_b3(&mut self, instruction: &[u8]) -> u8 {
        let ram_address_low = instruction[1] as u16;
        let ram_address_high = ((instruction[0] & 0b00010000) as u16) << 4;
        let ram_address = ram_address_low | ram_address_high;
        let bit_address = instruction[0] & 0b00000111;

        let mask = 0xFF & (0b0 << bit_address);

        let data = self.read_ram_value(ram_address);
        self.write_ram_value(ram_address, data & mask);

        1
    }

    fn inc_d9(&mut self, instruction: &[u8]) -> u8 {
        let ram_address_low = instruction[1] as u16;
        let ram_address_high = ((instruction[0] & 0x01) as u16) << 8;
        let address = ram_address_high | ram_address_low;
        let value = self.read_ram_value(address) + 1;
        self.write_ram_value(address, value);

        1
    }

    fn jmpf_a16(&mut self, instruction: &[u8]) -> u8 {
        let low_byte = instruction[2] as u16;
        let high_byte = (instruction[1] as u16) << 8;

        self.program_counter = low_byte | high_byte;

        2
    }

    fn ld_d9(&mut self, instruction: &[u8]) -> u8 {
        let address_high = ((instruction[0] & 0x01) as u16) << 8;
        let address_low = instruction[1] as u16;
        let address = address_low | address_high;
        let data = self.read_ram_value(address);
        self.write_ram_value(ACC_PTR, data);

        1
    }

    fn ldc(&mut self, instruction: &[u8]) -> u8 {
        let trl = self.read_ram_value(TRL_PTR) as u16;
        let trh = (self.read_ram_value(TRH_PTR) as u16) << 8;
        let tr = trl | trh;
        let acc = self.read_ram_value(ACC_PTR) as u16;

        //TODO: ACC might be signed, check this
        let addr = acc + tr;
        let acc = self.rom[addr as usize];
        self.write_ram_value(ACC_PTR, acc);

        2
    }

    fn mov_i8_d9(&mut self, instruction: &[u8]) -> u8 {
        let value = instruction[2];
        let address_low = instruction[1] as u16;
        let address_high = ((instruction[0] & 0x01) as u16) << 8;
        let address = address_low | address_high;

        self.write_ram_value(address, value);


        2
    }

    fn mov_i8_ri(&mut self, instruction: &[u8]) -> u8 {
        let value = instruction[1];
        let register = instruction[0] & 0x03;
        let address = self.get_indirect_address(register);
        self.write_ram_value(address, value);

        1
    }

    fn nop(&mut self, _instruction: &[u8]) -> u8 {
        1
    }

    fn pop_d9(&mut self, instruction: &[u8]) -> u8 {
        let addr_low = instruction[1] as u16;
        let addr_high = ((instruction[0] & 0x01) as u16) << 8;
        let addr = addr_high | addr_low;

        let data = self.stack_pop();
        self.write_ram_value(addr, data);

        2
    }

    fn push_d9(&mut self, instruction: &[u8]) -> u8 {
        let ram_address_low = instruction[1] as u16;
        let ram_address_high = ((instruction[0] & 0x01) as u16) << 8;
        let ram_address = ram_address_low | ram_address_high;

        let data = self.read_ram_value(ram_address);
        self.stack_push(data);
        2
    }

    fn ret(&mut self, _instruction: &[u8]) -> u8 {
        let pc_high = (self.stack_pop() as u16) << 8;
        let pc_low = self.stack_pop() as u16;
        let new_pc = pc_high | pc_low;

        println!("Returning from function to address {:X}", new_pc);
        self.program_counter = new_pc;
        2
    }

    fn set1_d9_b3(&mut self, instruction: &[u8]) -> u8 {
        let ram_address_low = instruction[1] as u16;
        let ram_address_high = ((instruction[0] & 0b00010000) as u16) << 4;
        let ram_address = ram_address_low | ram_address_high;
        let bit_address = instruction[0] & 0b00000111;

        let mask = 0x00 | (0b1 << bit_address);

        let data = self.read_ram_value(ram_address);
        self.write_ram_value(ram_address, data | mask);
        1
    }

    fn st_d9(&mut self, instruction: &[u8]) -> u8 {
        let address_high = ((instruction[0] & 0x01) as u16) << 8;
        let address_low = instruction[1] as u16;
        let address = address_low | address_high;

        let data = self.read_ram_value(ACC_PTR);
        self.write_ram_value(address, data);
        1
    }

    fn st_ri(&mut self, instruction: &[u8]) -> u8 {
        let register = instruction[0] & 0x03;
        let address = self.get_indirect_address(register);
        let acc = self.read_ram_value(ACC_PTR);
        self.write_ram_value(address, acc);
        1
    }

    fn xor_d9(&mut self, instruction: &[u8]) -> u8 {
        let address_low = instruction[1] as u16;
        let address_high = ((instruction[0] & 0x01) as u16) << 8;
        let address = address_low | address_high;
        let value = self.read_ram_value(address);
        let a = self.read_ram_value(ACC_PTR);

        let result = a^value;
        self.write_ram_value(ACC_PTR, result);
        1
    }

    fn unimplemented(&mut self, instruction: &[u8]) -> u8 {
        panic!("Unimplmented Instruction at 0x{:04X}: 0x{:02X} - {}", self.program_counter - OPCODES_86K[instruction[0] as usize].num_bytes as u16, instruction[0], OPCODES_86K[instruction[0] as usize].name);
    }
}
