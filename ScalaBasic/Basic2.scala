class Basic2 {

}


class ApplyTest{
  def apply() = "对象调用该方法"
  def test: Unit ={
    println("Test")
  }
}

// object将类中方法视为static method
// object代表自己，不能产生实例
object ApplyTest{
  def static: Unit ={
    println("静态方法")
  }

  // 类名调用该方法
  def apply() = new ApplyTest
}


object Main extends App{
  val a = ApplyTest()  // object中的apply
  a.test

  val b = new ApplyTest()  // class中的apply
  println(b())
}