class classBasic {

}

class Person {
  var name: String = _  // getter and setter
  val age = 10  // getter only
  private[this] val gender = "male"
}

// 没有val和var声明的参数，默认为private[this]
class Person2(val name: String, val age:Int){
  println("这是主构造器，执行类中所有可执行语句")
  var gender: String = _
  val school = "THU"

  // 附属构造器。必须首先调用已经存在的构造器
  def this(name:String, age:Int, gender:String){
    this(name, age)
    this.gender = gender
  }
}

class Student(name:String, age:Int, val major:String)extends Person2(name, age){
  println("继承自Person的子类。会执行子类的主构造器。")

  // 重写
  override val school = "STU"
  override def toString: String = super.toString
}



object Basic {
  def main(args: Array[String]){
    val p = new Person
    p.name = "Hi"
  }
}
