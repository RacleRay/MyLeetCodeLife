val l = List(1,2,3)

//map
val l2 = l.map((x:Int)=> x * 2)
val l3 = l.map(x => x * 2)
val l4 = l.map(2 * _)

//filter
l.filter(x => x % 2 == 0)
l.filter(_ % 2 == 0)

//zip
val a = List(1, 2, 3)
val b = List(4, 5, 6, 7)
a.zip(b)
a zip b

//partition
l.partition(_ % 2 == 0)

//flatten
val ll = List(List(1, 2), List(3, 4))
ll.flatten

//flatMap  map + flatten
ll.flatMap(x => x.map(_ * 2))

//Set
val s = Set(1, 2, 3)

//Tuple
val tuple1 = (1, 2)
println(tuple1._1)
println(tuple1._2)

//Map
val m = Map("a"->1, "b"->2)
println(m.get("b").getOrElse("None"))



