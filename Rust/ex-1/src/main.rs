use test_iter::miter;
use test_file::mfile;

use ex_1::lambda::run_closure;
use ex_1::thread::run_thread;

fn main() {
    mfile::run_file();
    miter::run_iter();

    run_closure();

    run_thread();
}
