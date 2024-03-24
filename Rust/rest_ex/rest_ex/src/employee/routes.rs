use crate::employee::{Empl, Emplss};
use crate::err_handler::CustomError;
use actix_web::{delete, get, post, put, web, HttpResponse};
use serde_json::json;


#[get("/employees")]
async fn find_all() -> Result<HttpResponse, CustomError> {
    let employees = web::block(||Emplss::find_all()).await.unwrap();
    Ok(HttpResponse::Ok().json(employees))
}


#[get("/employees/{id}")]
async fn find(id : web::Path<i32>) -> Result<HttpResponse, CustomError> {
    let employee = Emplss::find(id.into_inner())?;
    Ok(HttpResponse::Ok().json(employee))
}


#[post("/employees")]
async fn create(employee : web::Json<Empl>) -> Result<HttpResponse, CustomError> {
    let employee = Emplss::create(employee.into_inner())?;
    Ok(HttpResponse::Ok().json(employee))
}

#[put("/employees/{id}")]
async fn update(id : web::Path<i32>, employee:web::Json<Empl>) -> Result<HttpResponse, CustomError> {
    let employee = Emplss::update(id.into_inner(), employee.into_inner())?;
    Ok(HttpResponse::Ok().json(employee))
}

#[delete("/employees/{id}")]
async fn delete(id : web::Path<i32>) -> Result<HttpResponse, CustomError> {
    let deleted_employee = Emplss::delete(id.into_inner())?;
    Ok(HttpResponse::Ok().json(json!({"deleted": deleted_employee})))
}


pub fn init_routes(config: &mut web::ServiceConfig) {
    config.service(find_all);
    config.service(find);
    config.service(create);
    config.service(update);
    config.service(delete);
}