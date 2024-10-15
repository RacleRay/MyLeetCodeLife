fn dp_min_cash_num(
    amount: u32,
    cashes: &[u32],
    min_cashes: &mut [u32],
    cashes_used: &mut [u32],
) -> u32 {
    for target in 1..=amount {
        let mut min_cash_num = target;
        let mut used_cash = 1;
        for candi in cashes
            .iter()
            .filter(|&c| *c <= target)
            .collect::<Vec<&u32>>()
        {
            let sub_target_idx = (target - candi) as usize;
            let cash_num = 1 + min_cashes[sub_target_idx];
            if cash_num < min_cash_num {
                min_cash_num = cash_num;
                used_cash = *candi;
            }
        }

        min_cashes[target as usize] = min_cash_num;
        cashes_used[target as usize] = used_cash;
    }

    min_cashes[amount as usize]
}

fn print_res(cashes_used: &[u32], mut amount: u32) {
    while amount > 0 {
        let curr = cashes_used[amount as usize];
        println!("${curr}");
        amount -= curr;
    }
}

fn main() {
    let amount = 81u32;
    let cashes = [1, 5, 10, 20, 50];
    let mut min_cashes = [0u32; 82];
    let mut cashes_used = [0u32; 82];

    let optimal_num = dp_min_cash_num(amount, &cashes, &mut min_cashes, &mut cashes_used);

    println!("{amount} target use minimal {optimal_num} cashes.: ");
    print_res(&cashes_used, amount);
}
