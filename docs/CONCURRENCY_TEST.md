## Test: Distributed Multi-Instance Validation

### Objective

Verify that multiple server instances share the same Redis state and enforce a common rate limit.

### Configuration

- Server Instance 1 : localhost:8080
- Server Instance 2 : localhost:8081
- Shared Redis Storage
- Algorithm : Token Bucket
- Capacity : 10
- Refill Rate : 3 tokens/sec

### Procedure

1. Started two server instances:
   - Instance 1 on port 8080
   - Instance 2 on port 8081

2. Sent 10 requests to Server 1.

3. Immediately sent another 10 requests to Server 2 using the same API key/User ID.

### Results

Server 1

```
Allowed : 10
Rejected: 0
```

Server 2

```
Allowed : 0
Rejected: 10
```

### Observation

Since both server instances shared the same Redis storage, all available tokens were consumed by the first server instance. The second instance correctly observed the exhausted bucket and rejected all subsequent requests.

This confirms that rate limiting is enforced globally across multiple application instances.

### Status

✅ PASS