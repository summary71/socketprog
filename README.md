# Socket Programming Examples

TCP/UDP 소켓 프로그래밍 예제 모음입니다. C, Java, Python으로 작성되었습니다.

## 파일 구성

### C
| 파일 | 설명 |
|------|------|
| `server.c` / `client.c` | TCP 서버/클라이언트 |
| `serverorg.c` / `clientorg.c` | TCP 서버/클라이언트 — `select()` 사용 (아래 참고) |
| `udpserver.c` / `udpcli.c` | UDP 서버/클라이언트 |
| `wclientorg.cpp` / `wserverorg.cpp` | Windows용 TCP 서버/클라이언트 (Winsock) — `select()` 사용 (아래 참고) |

#### select()를 이용한 다중 소켓 처리

`serverorg.c` / `wserverorg.cpp` — **다중 클라이언트를 단일 프로세스로 처리하는 서버**
- `fd_set`에 리슨 소켓과 연결된 모든 클라이언트 소켓을 등록
- `select()` 호출로 활성화된 소켓만 골라 처리 (블로킹 없이 다중 소켓 감시)
- 리슨 소켓에 이벤트 → `accept()`로 새 클라이언트 수락 후 `fd_set`에 추가
- 클라이언트 소켓에 이벤트 → 데이터 수신 후 에코 응답, 연결 종료 시 `fd_set`에서 제거
- `serverorg.c`는 5초 타임아웃 설정, `wserverorg.cpp`는 타임아웃 없음(NULL)

`clientorg.c` / `wclientorg.cpp` — **소켓과 표준입력을 동시에 감시하는 클라이언트**
- `fd_set`에 서버 소켓(`sock`)과 표준입력(`stdin`) 두 개를 함께 등록
- `select()`로 두 입력을 동시에 대기하여 키보드 입력과 서버 응답을 모두 놓치지 않고 처리

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
