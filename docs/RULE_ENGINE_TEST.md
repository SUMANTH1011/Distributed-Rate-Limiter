# Rule Engine Testing Report

## Objective

Verify that the Rule Engine correctly:

- Matches requests to rules.
- Selects the highest-priority rule.
- Extracts the correct rate limiting key.
- Supports different key types.
- Reloads rules dynamically.
- Rejects invalid rule configurations.
- Caches rate limiter instances efficiently.

---

# Test Environment

| Component | Value |
|-----------|-------|
| OS | Windows 11 |
| Compiler | MSVC (C++23) |
| Storage | Redis |
| Web Framework | Crow |
| Build System | CMake |
| Containerization | Docker |

---

# Test Cases

## 1. Path Matching

### Request

GET /api/token

### Expected

- Correct rule matched.
- Token Bucket algorithm selected.

### Result

✅ PASS

---

## 2. Invalid Path

### Request

GET /api/unknown

### Expected

- No rule matched.
- Request allowed without rate limiting.

### Result

✅ PASS

---

## 3. HTTP Method Matching

### Request

POST /api/token

### Expected

- Rule ignored if configured only for GET.

### Result

✅ PASS

---

## 4. Rule Priority Selection

### Scenario

Configured multiple matching rules with different priorities.

### Expected

Lowest priority value selected.

### Result

✅ PASS

---

## 5. USER_ID Key Extraction

### Header

```
X-User-ID: sumanth
```

### Expected

```
Rate Limit Key = sumanth
```

Redis Keys

```
ratelimit:token:sumanth
```

### Result

✅ PASS

---

## 6. IP Key Extraction

### Configuration

```
keyType = IP
```

### Expected

```
Rate Limit Key = 127.0.0.1
```

Redis Keys

```
ratelimit:token:127.0.0.1
```

### Result

✅ PASS

---

## 7. API_KEY Extraction

### Header

```
X-API-Key: abc123
```

### Expected

```
Rate Limit Key = abc123
```

Redis Keys

```
ratelimit:token:abc123
```

### Result

✅ PASS

---

## 8. Rule Reload

### Procedure

- Modified rules.json
- Called

```
POST /reload
```

### Expected

- New rules loaded successfully.
- New configuration immediately applied.

### Result

✅ PASS

---

## 9. Invalid Rule Reload

### Procedure

Inserted invalid algorithm into rules.json.

### Expected

- Reload rejected.
- Existing rules remained active.

### Result

✅ PASS

---

## 10. Multiple Independent Users

### Requests

```
X-User-ID: sumanth
```

```
X-User-ID: alex
```

### Expected

Independent Redis keys

```
ratelimit:token:sumanth
ratelimit:token:alex
```

### Result

✅ PASS

---

## 11. Rate Limiter Cache

### First Request

Expected Log

```
Creating Limiter
```

### Subsequent Requests

Expected Log

```
Using Cached Limiter
```

### Result

✅ PASS

---

# Summary

| Test | Status |
|------|--------|
| Path Matching | ✅ PASS |
| Invalid Path | ✅ PASS |
| HTTP Method Matching | ✅ PASS |
| Rule Priority | ✅ PASS |
| USER_ID Key Extraction | ✅ PASS |
| IP Key Extraction | ✅ PASS |
| API_KEY Extraction | ✅ PASS |
| Rule Reload | ✅ PASS |
| Invalid Rule Handling | ✅ PASS |
| Multiple User Isolation | ✅ PASS |
| Limiter Cache | ✅ PASS |

---

# Conclusion

The Rule Engine successfully:

- Matched requests based on configured rules.
- Selected the correct rule using priority.
- Extracted USER_ID, IP, and API_KEY correctly.
- Reloaded rules dynamically without restarting the server.
- Preserved existing rules when invalid configurations were supplied.
- Created isolated Redis keys for different clients.
- Reused cached rate limiter instances for improved performance.

**Overall Status:** ✅ **All Rule Engine tests passed successfully.**