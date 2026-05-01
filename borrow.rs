fn main(){
    // We allocate a String in physical memory (RAM)
    let server_name = String::from("LedgerCore API");
    // We transfer "ownership" of that memory to a new variable
    let active_process = server_name;
    // We try to print the original variable
    println!("Booting up: {}", server_name);
}