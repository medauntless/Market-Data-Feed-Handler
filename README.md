# Market Data Feed Handler (C++20)

A simple C++20 project that simulates a market data feed handler with **Primary** and **Secondary** data feeds.

The project demonstrates how a consumer switches to a secondary feed when the primary feed produces invalid data and then returns to the primary feed.

> **Note:** This is a simplified educational implementation intended to demonstrate multithreading and failover concepts.

## Features

- Simulated primary and secondary market data feeds
- Automatic failover to the secondary feed
- Atomic shared state using `std::atomic`
- Three concurrent threads:
  - Primary feed producer
  - Secondary feed producer
  - Consumer
- Feed selection using an atomic enum
- Graceful shutdown of all threads

## Technologies

- C++20
- std::thread
- std::atomic
- std::chrono

## Build

```bash
g++ -std=c++20 -pthread main.cpp -o market_feed
```

Run:

```bash
./market_feed
```

## Current Workflow

1. The primary feed generates market data.
2. Data is validated before being published.
3. If validation fails, the consumer switches to the secondary feed.
4. The secondary feed continues providing data until the system switches back to the primary feed.

## Future Improvements

- Recovery validation before switching back to the primary feed
- Heartbeat monitoring
- Sequence number validation
- Lock-free queue for message passing
- Feed latency measurement
- Configurable failover strategy
- Logging framework
