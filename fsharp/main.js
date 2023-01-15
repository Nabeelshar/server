open Giraffe

let app =
    choose [
        route "hello" >=> text "Hello, World!"
    ]

let server =
    startWebServer defaultWebServerOptions app

[<EntryPoint>]
let main argv =
    server.Run()
    0
