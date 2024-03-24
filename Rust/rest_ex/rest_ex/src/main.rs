#[macro_use]
extern crate diesel;

#[macro_use]
extern crate diesel_migrations;

use actix_web::{App, HttpServer};
use dotenv::dotenv;
use listenfd::ListenFd;
use std::env;

mod schema;
mod err_handler;
mod db;
mod employee;

#[actix_rt::main]
async fn main() -> std::io::Result<()> {
    dotenv().ok();
    db::init();

    let mut listenfd = ListenFd::from_env();
    let mut server = HttpServer::new(|| App::new().configure(employee::init_routes));

    server = match listenfd.take_tcp_listener(0)? {
        Some(listenfd) => server.listen(listenfd)?,
        None => {
            let host = env::var("HOST").expect("HOST must be set");
            let port = env::var("PORT").expect("PORT must be set");
            server.bind(format!("{}:{}", host, port))?
        }
    };

    server.run().await
}

