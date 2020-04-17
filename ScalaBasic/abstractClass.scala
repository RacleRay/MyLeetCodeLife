class abstractClass {

}


abstract class Person {
  def speak

  val name: String
  var age: Int
}

class Student extends Person {
  def speak: Unit = {
    println("不需要override字段")
  }

  val name = "Allen"
  var age = 12
}


// 类似java中的interface，同时自带default method
trait Logger{
  def log(msg: String): Unit ={
    println("log: " + msg)
  }
}

class Impliment extends Logger{
  def print(msg: String): Unit ={
    log(msg)
  }
}


abstract class Client{
  def act(opt: String)
}

// 同时对象也可以with某一种trait(特质),可以有多种特质
class MyClient extends Client with Logger{
  def act(opt: String): Unit ={
    log(opt)
  }
}

