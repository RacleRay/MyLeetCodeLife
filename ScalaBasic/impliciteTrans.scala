
// 向类库中添加自定义的方法，在scala中很容易实现，而Java很难受
class A{
}


class RichA(a: A){
  def rich: Unit ={
    println("rich...")
  }
}


object Test extends App{
  // implicit transform
  implicit def a2RichA(a: A) = new RichA(a)

  val a = new A
  a.rich


  // implicit variables
  def test(implicit name: String): Unit ={
    println(name)
  }
  implicit val name = "implicite"
  test  //直接使用
  test("New Name")  // 更改


  // implicit class
  implicit class Calculator(x: Int){
    def add(a: Int) :Int = a + 1
  }
  println(1.add(1))  // 直接识别1为 Int , 隐式调用了Calculator
}