# RAW HTTP Request

    GET / HTTP/1.1
    Host: localhost:8080
    User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/118.0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
    Accept-Language: en-US,en;q=0.5
    Accept-Encoding: gzip, deflate, br
    Connection: keep-alive
    Upgrade-Insecure-Requests: 1
    Sec-Fetch-Dest: document
    Sec-Fetch-Mode: navigate
    Sec-Fetch-Site: none
    Sec-Fetch-User: ?1

# TODO

- remodel models to use inside struct
- implement database initialization and bootstrap some data
- finish database actions (save, load, remove)
- read socket in seperate thread
- implement product endpoint
- implement category endpoint
- implement homepage endpoint
- implement cart endpoint
- implement user endpoint
- implement login endpoint
