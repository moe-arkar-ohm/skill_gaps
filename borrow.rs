fn main() {
    // 1. We declare the original memory as mutable (changeable)
    let mut server_name = String::from("LedgerCore API");
    
    // 2. We hand out a single Renovation Key (&mut)
    let active_process = &mut server_name; 
    
    // 3. The borrower uses the key to change the original memory
   active_process.push_str(" - v2.0 (Stable Environment)");
    println!("Original memory: {}", server_name); // The Guest Key
    println!("System Status: {}", active_process); // The Renovation Key
}