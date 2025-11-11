#pragma once

#include <string>
#include <map>

/**
 * TODO: Implement a Monitoring System
 * 
 * Requirements:
 * - Collect metrics (counters, gauges, histograms)
 * - Store time-series data
 * - Query metrics
 * - Alert on thresholds
 * 
 * Features:
 * - recordMetric(name, value, timestamp)
 * - getMetric(name, start_time, end_time)
 * - setAlert(name, threshold, callback)
 * - getSystemStats() - CPU, memory, etc.
 * 
 * Implementation hints:
 * - Use std::map for metric storage
 * - Use std::chrono for timestamps
 * - Read /proc for system stats (Linux)
 */

// TODO: Implement MonitoringSystem class
