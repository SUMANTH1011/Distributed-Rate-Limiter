# To run the project .\build\Debug\DistributedRateLimiter.exe

# Distributed Rate Limiter - Testing Report

## Test Environment

- OS: Windows 11
- Compiler: MSVC (C++23)
- Redis: Redis Server 7.x
- Web Framework: Crow
- Storage: Redis
- Build System: CMake
- Containerization: Docker & Docker Compose

---

# Functional Testing

## 1. Server Startup

| Test | Expected | Result |
|------|----------|--------|
| Server Starts | Server starts successfully | ✅ PASS |
| Redis Connection | Connected successfully | ✅ PASS |
| Rules Loaded | All rules loaded | ✅ PASS |
| Metrics Reporter | Running | ✅ PASS |

---

## 2. Health Endpoint

Endpoint

GET /health

Expected

HTTP 200

Result

✅ PASS

---

## 3. Root Endpoint

Endpoint

GET /

Expected

Service information JSON

Result

✅ PASS

---

## 4. Metrics Endpoint

Endpoint

GET /metrics

Expected

Returns current statistics in JSON format

Result

✅ PASS

---

# Rate Limiting Algorithms

## Token Bucket

Configuration

- Capacity = Tested
- Refill Rate = Tested

Results

- Requests allowed until bucket exhausted
- Requests rejected after capacity reached
- Bucket refilled correctly

Status

✅ PASS

---

## Fixed Window

Configuration

- Fixed request limit
- Fixed window duration

Results

- Allowed requests inside window
- Rejected requests after limit
- Counter reset after window expiration

Status

✅ PASS

---

## Leaky Bucket

Configuration

- Bucket Capacity Tested
- Leak Rate Tested

Results

- Burst requests accepted until bucket full
- Overflow requests rejected
- Bucket leaked correctly over time

Status

✅ PASS

---

## Sliding Window Log

Configuration

- Window Size Tested
- Request Limit Tested

Results

- Old requests removed correctly
- Limit enforced accurately

Status

✅ PASS

---

## Sliding Window Counter

Configuration

- Window Size Tested
- Request Limit Tested

Results

- Weighted previous window calculated correctly
- Smooth rate limiting observed

Status

✅ PASS

---

# Metrics Verification

Final Metrics

```json
{
  "requestsPerSecond": 0.26227208976157085,
  "uptimeSeconds": 713,
  "totalRequests": 187,
  "ruleReloads": 0,
  "redisCalls": 82,
  "allowedRequests": 140,
  "rejectedRequests": 45,
  "redisFailures": 2,
  "algorithms": {
    "SLIDING_WINDOW_COUNTER": 8,
    "TOKEN_BUCKET": 24,
    "FIXED_WINDOW": 18,
    "LEAKY_BUCKET": 21,
    "SLIDING_WINDOW_LOG": 9
  }
}
```

Observations

- Total Requests processed successfully
- All five algorithms executed successfully
- Redis operations recorded correctly
- Metrics collected correctly
- Redis failures occurred only during connection testing

Status

✅ PASS

---

# Docker Testing

| Test | Result |
|------|--------|
| Docker Build | ✅ PASS |
| Docker Compose | ✅ PASS |
| Redis Container | ✅ PASS |
| Rate Limiter Container | ✅ PASS |

---

# Overall Result

| Component | Status |
|-----------|--------|
| Rule Engine | ✅ PASS |
| Redis Storage | ✅ PASS |
| Token Bucket | ✅ PASS |
| Fixed Window | ✅ PASS |
| Leaky Bucket | ✅ PASS |
| Sliding Window Log | ✅ PASS |
| Sliding Window Counter | ✅ PASS |
| Metrics | ✅ PASS |
| Logging | ✅ PASS |
| Docker | ✅ PASS |

Overall Status

🎉 **All functional tests passed successfully.**