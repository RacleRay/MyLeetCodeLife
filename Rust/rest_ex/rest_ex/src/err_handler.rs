use std::fmt::Formatter;


#[derive(Debug, Deserialize)]
pub struct CustomError {
    pub err_status_code: u16,
    pub err_message: String
}


impl CustomError {
    pub fn new(err_status_code: u16, err_message: String) -> CustomError {
        CustomError {
            err_status_code,
            err_message
        }
    }
}


impl fmt::Display for CustomError {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        f.write_str(self.err_message.as_str())
    }
}


impl From<DiselError> for CustomError {
    fn from(error: DiselError) -> CustomError {
        match error {
            DiselError::DatabaseError(_, err) => CustomError::new(
                409, err.message().to_string()
            ),
            DiselError::NotFound => {
                CustomError(404, "employee not found".to_string())
            },
            err => CustomError::new(500,
                format!("Unknown error! {}", err)
            )
        }
    }
}


