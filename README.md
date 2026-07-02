# 🚀 Distributed Rate Limiter

A high-performance **Distributed Rate Limiter** built in **C++23** using **Crow**, **Redis**, **Lua Scripting**, and **Docker**.

The project provides a flexible and scalable rate-limiting solution that supports multiple algorithms, dynamic rule management, centralized Redis storage, real-time metrics collection, structured logging, and distributed deployment across multiple server instances.

It is designed to simulate how modern API Gateways and cloud services enforce request limits while maintaining consistency across multiple application instances.

---

## ✨ Features

- 🚀 Supports **5 Rate Limiting Algorithms**
  - Token Bucket
  - Fixed Window
  - Sliding Window Log
  - Sliding Window Counter
  - Leaky Bucket

- ⚡ Dynamic Rule Engine
  - Path Matching
  - HTTP Method Matching
  - User ID Based Rules
  - IP Based Rules
  - API Key Based Rules
  - Rule Priorities

- 🔄 Runtime Rule Reloading

- 📊 Metrics Collection
  - Total Requests
  - Allowed Requests
  - Rejected Requests
  - Redis Calls
  - Redis Failures
  - Algorithm Usage

- 📝 Structured Logging

- 🐳 Docker Support

- 🐳 Docker Compose Support

- 🔴 Redis Integration

- ⚙️ Lua Script Based Atomic Operations

- 🌐 Multi-threaded HTTP Server

- 📈 Distributed Deployment

---

# 🏗️ System Architecture

```text
                    +----------------------+
                    |      HTTP Client     |
                    | (Browser / Postman)  |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |    Crow HTTP Server  |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |   Request Handler    |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |     Rule Engine      |
                    +----------+-----------+
                               |
              +----------------+----------------+
              |                                 |
              v                                 v
     +------------------+             +----------------------+
     |   Rule Matcher   |             | RateLimiter Manager  |
     +------------------+             +----------+-----------+
                                                 |
                                                 v
                                   +----------------------------+
                                   |   Rate Limiter Factory     |
                                   +-------------+--------------+
                                                 |
               +---------------------------------+--------------------------------+
               |                |                |               |                |
               v                v                v               v                v
      Token Bucket     Fixed Window     Sliding Log     Sliding Counter    Leaky Bucket
               \                |                |               |                /
                \_______________|________________|_______________|_______________/
                                                |
                                                v
                                     +----------------------+
                                     |   Redis Storage      |
                                     +----------+-----------+
                                                |
                                                v
                                     +----------------------+
                                     |  Redis Lua Scripts   |
                                     +----------+-----------+
                                                |
                                                v
                                     +----------------------+
                                     |      Redis Server    |
                                     +----------------------+
```

---

# 🔄 Request Flow

1. Client sends an HTTP request.
2. Crow HTTP Server receives the request.
3. Request Handler creates a `RequestContext`.
4. Rule Engine finds the highest-priority matching rule.
5. RateLimiterManager retrieves or creates the required rate limiter.
6. The selected algorithm executes using Redis and Lua scripts.
7. The request is either **Allowed (200)** or **Rejected (429)**.
8. Metrics and logs are updated before sending the response back to the client.

---

# 📂 Project Structure

```text
Distributed-Rate-Limiter/
│
├── config/
│   ├── logging.json          # Logging configuration
│   ├── redis.json            # Redis configuration
│   └── server.json           # Server configuration
│
├── docs/
│   ├── TESTING.md
│   ├── RULE_ENGINE_TEST.md
│   ├── CONCURRENCY_TEST.md
│
├── src/
│   ├── algorithms/
│   │   ├── FixedWindow.cpp
│   │   ├── TokenBucket.cpp
│   │   ├── LeakyBucket.cpp
│   │   ├── SlidingWindowLog.cpp
│   │   └── SlidingWindowCounter.cpp
│   │
│   ├── config/
│   ├── factory/
│   ├── logging/
│   ├── manager/
│   ├── monitoring/
│   ├── request/
│   ├── rule_engine/
│   ├── server/
│   ├── storage/
│   ├── synchronization/
│   └── utils/
│
├── Dockerfile
├── docker-compose.yml
├── CMakeLists.txt
├── main.cpp
├── rules.json
├── README.md
├── LICENSE
├── .gitignore
└── .dockerignore
```

---

# ⚙️ Core Components

| Component | Responsibility |
|-----------|----------------|
| **Crow HTTP Server** | Accepts incoming HTTP requests |
| **Request Handler** | Converts HTTP requests into internal request objects |
| **Rule Engine** | Matches incoming requests to configured rules |
| **Rule Matcher** | Selects the highest-priority matching rule |
| **RateLimiter Manager** | Creates and caches rate limiter instances |
| **RateLimiter Factory** | Instantiates the correct algorithm |
| **Algorithms** | Implements Token Bucket, Fixed Window, Leaky Bucket, Sliding Window Log, and Sliding Window Counter |
| **Redis Storage** | Executes Redis commands and Lua scripts |
| **Metrics Collector** | Tracks request statistics and algorithm usage |
| **Logger** | Records structured application logs |
| **Rule Synchronizer** | Reloads rules dynamically without restarting the server |

---

# ⚡ Supported Rate Limiting Algorithms

The system supports five industry-standard rate limiting algorithms. Each algorithm is implemented independently and can be selected dynamically through the rule configuration.

| Algorithm | Description | Best Use Case |
|------------|-------------|---------------|
| **Token Bucket** | Tokens are generated at a fixed rate. Each request consumes one token. Requests are rejected when no tokens are available. | APIs allowing controlled bursts of traffic |
| **Fixed Window** | Counts requests within a fixed time window. The counter resets when the window expires. | Simple API rate limiting |
| **Sliding Window Log** | Stores timestamps of every request and removes expired entries to provide precise rate limiting. | High-accuracy request limiting |
| **Sliding Window Counter** | Combines the current and previous time windows using weighted calculations to reduce boundary issues. | Smooth request limiting with lower memory usage |
| **Leaky Bucket** | Requests enter a bucket and leave at a constant rate, smoothing burst traffic. | Traffic shaping and steady request processing |

---

## Algorithm Selection

The algorithm is selected dynamically from `rules.json`.

Example:

```json
{
    "algorithm": "TOKEN_BUCKET",
    "keyType": "USER_ID",
    "capacity": 10,
    "refillRate": 3
}
```

Changing the configuration does **not** require recompiling the application. Rules can be reloaded dynamically using the `/reload` endpoint.

---

## Supported Key Types

The Rule Engine supports multiple strategies for identifying clients.

| Key Type | Description |
|----------|-------------|
| **USER_ID** | Rate limits are applied per user using the `X-User-ID` header. |
| **API_KEY** | Limits are applied using an API key supplied in the `X-API-Key` header. |
| **IP** | The client's IP address is used as the rate limiting key. |

This allows the same server to support different rate limiting policies for different APIs.

---

# 🚀 Getting Started

## Prerequisites

Before running the project, ensure the following tools are installed:

- C++23 compatible compiler (MSVC / GCC / Clang)
- CMake (3.20 or later)
- Git
- Docker & Docker Compose (optional)
- Redis Server
- vcpkg

---

# 📥 Clone the Repository

```bash
git clone https://github.com/<YOUR_GITHUB_USERNAME>/Distributed-Rate-Limiter.git

cd Distributed-Rate-Limiter
```

Replace `<YOUR_GITHUB_USERNAME>` with your GitHub username.

---

# 📦 Install Dependencies

The project uses **vcpkg** for dependency management.

Install the required libraries:

```bash
./vcpkg install crow hiredis redis-plus-plus nlohmann-json
```

---

# ⚙ Configure the Project

Update the configuration files located in the `config/` directory.

### Redis Configuration

```json
{
    "host": "127.0.0.1",
    "port": 6379
}
```

### Server Configuration

```json
{
    "host": "0.0.0.0",
    "port": 8080,
    "threads": 8
}
```

---

# 🔨 Build the Project

Generate build files using CMake:

```bash
cmake -S . -B build ^
-DCMAKE_TOOLCHAIN_FILE=<VCPKG_ROOT>/scripts/buildsystems/vcpkg.cmake ^
-DCMAKE_PREFIX_PATH=<VCPKG_ROOT>/installed/x64-windows
```

Build the project:

```bash
cmake --build build
```

---

# ▶ Run the Server

Default port:

```bash
./build/Debug/DistributedRateLimiter.exe
```

Run on a custom port:

```bash
./build/Debug/DistributedRateLimiter.exe 8081
```

---

# 🔴 Start Redis

Windows

Run your local Redis server before starting the application.

Linux / WSL

```bash
sudo service redis-server start
```

Verify Redis:

```bash
redis-cli ping
```

Expected output:

```text
PONG
```

---

# 🐳 Running with Docker

Build the Docker image:

```bash
docker build -t distributed-rate-limiter .
```

Run using Docker Compose:

```bash
docker compose up
```

The application will start along with a Redis container.

---

# 📡 REST API Reference

The Distributed Rate Limiter exposes the following REST endpoints.

---

## Root Endpoint

Returns basic service information.

**Request**

```http
GET /
```

**Response**

```json
{
    "service": "Distributed Rate Limiter",
    "version": "1.0",
    "status": "UP"
}
```

---

## Health Check

Checks whether the server is running.

**Request**

```http
GET /health
```

**Response**

```text
Service is UP
```

Status Code

```
200 OK
```

---

## Metrics

Returns runtime metrics collected by the server.

**Request**

```http
GET /metrics
```

Example Response

```json
{
    "requestsPerSecond": 0.26,
    "uptimeSeconds": 713,
    "totalRequests": 187,
    "allowedRequests": 140,
    "rejectedRequests": 45,
    "redisCalls": 82,
    "redisFailures": 2,
    "ruleReloads": 0,
    "algorithms": {
        "TOKEN_BUCKET": 24,
        "FIXED_WINDOW": 18,
        "LEAKY_BUCKET": 21,
        "SLIDING_WINDOW_LOG": 9,
        "SLIDING_WINDOW_COUNTER": 8
    }
}
```

---

# Rate Limited APIs

These endpoints are protected using the configured rate limiting rules.

---

## Token Bucket

```http
GET /api/token
```

Example Header

```
X-User-ID: sumanth
```

---

## Fixed Window

```http
GET /api/fixed
```

Example Header

```
X-User-ID: sumanth
```

---

## Leaky Bucket

```http
GET /api/leaky
```

Example Header

```
X-User-ID: sumanth
```

---

## Sliding Window Log

```http
GET /api/log
```

Example Header

```
X-User-ID: sumanth
```

---

## Sliding Window Counter

```http
GET /api/counter
```

Example Header

```
X-User-ID: sumanth
```

---

## Reload Rules

Reloads `rules.json` without restarting the server.

```http
POST /reload
```

Response

```
Rules Reloaded
```

---

# Response Codes

| Status Code | Description |
|-------------|-------------|
| **200 OK** | Request successfully processed |
| **429 Too Many Requests** | Rate limit exceeded |
| **500 Internal Server Error** | Server or Redis error |

---

# 📊 Logging

The application includes a thread-safe logging system that records important runtime events.

### Logged Events

- Server startup
- Incoming HTTP requests
- Rule matching
- Selected rate limiting algorithm
- Rate limiter creation and cache reuse
- Rate limit decisions
- Redis connection failures
- Rule reload events

### Example

```text
[2026-07-01 11:46:18] [INFO] Incoming Request | IP=127.0.0.1 | User=sumanth | Method=GET | Path=/api/token
[2026-07-01 11:46:18] [INFO] Matched Rule | RuleID=1 | Priority=1
[2026-07-01 11:46:18] [INFO] Creating Limiter | RuleID=1
[2026-07-01 11:46:18] [DEBUG] Rate Limit Key | sumanth
[2026-07-01 11:46:18] [INFO] Decision | ALLOWED | RuleID=1
```

---

# 📈 Metrics

The server continuously tracks runtime metrics.

Collected Metrics include:

- Total Requests
- Allowed Requests
- Rejected Requests
- Requests Per Second
- Redis Calls
- Redis Failures
- Rule Reload Count
- Algorithm Usage
- Server Uptime

Example Metrics

```json
{
    "requestsPerSecond": 0.262,
    "uptimeSeconds": 713,
    "totalRequests": 187,
    "allowedRequests": 140,
    "rejectedRequests": 45,
    "redisCalls": 82,
    "redisFailures": 2,
    "ruleReloads": 0,
    "algorithms": {
        "TOKEN_BUCKET": 24,
        "FIXED_WINDOW": 18,
        "LEAKY_BUCKET": 21,
        "SLIDING_WINDOW_LOG": 9,
        "SLIDING_WINDOW_COUNTER": 8
    }
}
```

---

# 🧪 Testing

The project has been thoroughly tested.

## Functional Testing

- ✅ Token Bucket
- ✅ Fixed Window
- ✅ Leaky Bucket
- ✅ Sliding Window Log
- ✅ Sliding Window Counter
- ✅ Metrics
- ✅ Logging
- ✅ Redis Integration

Documentation:

- `docs/TESTING.md`

---

## Rule Engine Testing

Verified:

- Rule Matching
- Rule Priority
- User ID Extraction
- API Key Extraction
- IP Extraction
- Rule Reload
- Invalid Rule Handling
- Cached Rate Limiter Reuse

Documentation:

- `docs/RULE_ENGINE_TEST.md`

---

## Concurrency Testing

Verified:

- Concurrent requests
- Multiple users
- Thread safety
- Shared Redis state
- Distributed deployment
- Multi-instance synchronization

Documentation:

- `docs/CONCURRENCY_TEST.md`

---

# 🐳 Docker

The project supports Docker deployment.

Build

```bash
docker build -t distributed-rate-limiter .
```

Run

```bash
docker compose up
```

Docker Compose starts:

- Rate Limiter Server
- Redis Server

---

# 📷 Project Screenshots

You can include screenshots here.

Examples:

- Server Startup
- Metrics Endpoint
- Redis Keys
- Docker Containers
- Rule Reload
- Concurrent Requests
- Logging Output

---

# 🚀 Future Improvements

Possible future enhancements include:

- Redis Pub/Sub based rule synchronization
- Distributed metrics aggregation
- Prometheus integration
- Grafana dashboards
- JWT authentication
- gRPC support
- Kubernetes deployment
- Redis Cluster support
- Admin Dashboard
- Web-based Rule Management
- OpenTelemetry tracing
- Rate limiting analytics

---

# 📚 Documentation

Additional documentation is available in the `docs/` directory.

| File | Description |
|------|-------------|
| `TESTING.md` | Functional testing results |
| `RULE_ENGINE_TEST.md` | Rule engine validation |
| `CONCURRENCY_TEST.md` | Concurrent and distributed testing |

---

# 🤝 Contributing

Contributions are welcome.

1. Fork the repository.
2. Create a new feature branch.
3. Commit your changes.
4. Push the branch.
5. Open a Pull Request.

---

# 👨‍💻 Author

**Sumanth Reddy**

Computer Science Engineering Student

Dayananda Sagar College of Engineering

GitHub:

```
https://github.com/SUMANTH1011/Distributed-Rate-Limiter
```

---

# 📄 License

This project is licensed under the **MIT License**.

See the `LICENSE` file for more information.

---

# ⭐ Support

If you found this project useful:

⭐ Star the repository

🍴 Fork it

🛠️ Contribute improvements

Thank you for checking out this project!