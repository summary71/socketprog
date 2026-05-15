# Socket Programming Examples

TCP/UDP 소켓 프로그래밍 예제 모음입니다. C, Java, Python으로 작성되었습니다.

## 파일 구성

### C
| 파일 | 설명 |
|------|------|
| `server.c` / `client.c` | TCP 서버/클라이언트 |
| `serverorg.c` / `clientorg.c` | TCP 서버/클라이언트 (원본) |
| `udpserver.c` / `udpcli.c` | UDP 서버/클라이언트 |
| `wclientorg.cpp` / `wserverorg.cpp` | Windows용 TCP 서버/클라이언트 (Winsock) |

### Java
| 파일 | 설명 |
|------|------|
| `TCPServer.java` / `TCPClient.java` | TCP 서버/클라이언트 |
| `TCPServerTh.java` / `TCPClientTh.java` | 멀티스레드 TCP 서버/클라이언트 |
| `SimpleThreads.java` | 스레드 기본 예제 |

### Python
| 파일 | 설명 |
|------|------|
| `tcpsrv.py` / `tcpcli.py` | TCP 서버/클라이언트 |
| `udpsrv.py` / `udpcli.py` | UDP 서버/클라이언트 |

## 빌드 (C)

```bash
make
```

## 실행 예시 (C, TCP)

```bash
# 서버 먼저 실행
./srv

# 클라이언트 실행
./cli <서버IP>
```
