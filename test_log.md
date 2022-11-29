## 测试 1

| 参数       | size    | size    | size    |
| ---------- | ------- | ------- | ------- |
| batch      | 1       | 2       | 5       |
| time       | 60s     |
| frequence  | 40khz   |
| pulse_size | 416B    |
| recv       | 2465769 | 1248644 | 489108  |
| memcpy     | 2475733 | 1235154 | 494379  |
| write hdf5 | 2492137 | 1249126 | 490201  |
| total      |         | 2497288 | 2445540 |

## 测试 2

| 参数       | size     | size     | size     |
| ---------- | -------- | -------- | -------- |
| batch      | 1        | 2        | 5        |
| time       | 300s     |
| frequence  | 40khz    |
| pulse_size | 416B     |
| recv       | 11996268 | 6024164  | 2427560  |
| memcpy     |          |          |          |
| write hdf5 |          |          |          |
| total      |          | 12048328 | 12137800 |

## 测试 3

| 参数       | size    | size    | size    |
| ---------- | ------- | ------- | ------- |
| batch      | 1       | 2       | 5       |
| time       | 60s     |
| frequence  | 80khz   |
| pulse_size | 416B    |
| recv       | 4954883 | 2409699 | 963855  |
| memcpy     |         |         |         |
| write hdf5 |         |         |
| total      |         | 4819398 | 4819275 |
