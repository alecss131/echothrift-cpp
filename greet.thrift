namespace java ru.test

service Greet {
   HelloReply sayHello(1:HelloRequest message)
}

struct HelloRequest {
  1: string name
}

struct HelloReply {
  1: string message
}
