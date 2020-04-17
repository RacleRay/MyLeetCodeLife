class Basic {

}

object Basic {
  def hello(name: String = "Paul"): String = {
    return "Hello, " + name
  }

  val add = (x: Int, y: Int) => x + y

  def mult(x: Int)(y: Int) = x * y

  def printMult(c: String*) = {
    c.foreach(x => println(x))
  }

  def testWhile(init: Int) = {
    var (i, step) = (init, 1)
    while (i < 10) {
      i = i + step
    }
    println(i)
  }

  def testFor(init: Int) = {
    for (i <- 1 to 10 if i % 2 == 0) {
      println(i)
    }
  }

  def main(args: Array[String]): Unit = {
    println(hello("world!"))
    println(hello())

    println(add(1, 2))

    println(mult(2)(3))

    printMult("a", "b", "c")
  }
}