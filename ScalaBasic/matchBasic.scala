// case class默认为val 参数。不用new就可以产生对象。
case class Book(name:String, author:String)


object Match extends App{
  var value: Int = 3
  val res = value match{
    case 1 => "1"
    case 2 => "2"
    case _ => "None"
  }

  val res2 = value match{
    case i if i == 1 => "1"
    case i if i == 2 => "2"
    case _ => "None"
  }

  val book1 = Book("Name1", "Author1")
  book1 match{
    case Book(name, author) => println("这是一本书")
    case _ => println("None")
  }
}


def func(obj: Any) = obj match{
  case x : Int => println("Int")
  case s : String => println("String")
}