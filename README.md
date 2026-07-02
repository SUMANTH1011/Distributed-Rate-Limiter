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