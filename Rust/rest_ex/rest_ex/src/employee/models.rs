use crate::db;
use crate::err_handler::CustomError;
use crate::schema::employees;
use diesel::prelude::*;
use serde::{Deserialize, Serialize};


#[derive(Serialize, Deserialize, AsChangeset, Insertable)]
#[table_name = "employees"]
pub struct Empl {
    pub first_name: String,
    pub last_name: String,
    pub department: String,
    pub salary: i32,
    pub age: i32,
}


#[derive(Serialize,Deserialize,AsChangeset,Insertable)]
pub struct Emplss {
    pub first_name: String,
    pub last_name: String,
    pub department: String,
    pub salary: i32,
    pub age: i32,
}

impl Emplss {
    pub fn find_all() -> Result<Vec<Self>, CustomError> {
        let conn = db::connection()?;
        let employees = employees::table.load::<Emplss>(&conn)?;
        Ok(employees)
    }

    pub fn find(id : i32) -> Result<Self, CustomError> {
        let conn = db::connection()?;
        let employee = employees::table.filter(employees::id.eq(id));
        Ok(employee)
    }   

    pub fn create(employee : Empl) -> Result<Self, CustomError> {
        let conn = db::connection();
        let employee = Empl::from(employee);
        let employee = diesel::insert_into(employees::table)
            .values(employee).get_result(&conn)?;
        Ok(employee)
    }

    pub fn update(id : i32, employee: Empl) -> Result<Self, CustomError> {
        let conn = db::connection()?;
        let employee = diesel::update(employees::table)
            .filter(employees::id.eq(id)).set(employee).get_result(&conn)?;
        Ok(employee)
    }

    pub fn delete(id : i32) -> Result<usize, CustomError> {
        let conn = db::connection()?;
        let res = diesel::delete(employees::table.filter(employees::id.eq(id)))
            .excute(&conn)?;
        Ok(res)
    }
}


impl Empl {
    fn from(employee : Empl) -> Empl {
        Empl {
            first_name : employee.first_name,
            last_name : employee.last_name,
            department : employee.department,
            salary : employee.salary,
            age : employee.age,
        }
    }
}