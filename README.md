# RFID Collision Search Simulator

재귀 방식과 반복 방식의 RFID 태그 충돌 탐색 과정을 비교하기 위해 구현한 C++ 콘솔 프로젝트입니다.

## Tech Stack
- C++
- STL
- Visual Studio 2022

## Features
- 재귀 방식과 반복 방식의 탐색 흐름 및 결과 비교
- 질의 횟수, 충돌 횟수, 실행 시간 비교
- 정해진 데이터 / 사용자 직접 입력 / 랜덤 TAG 생성 지원

## Search Model
Prefix 기반 질의를 통해 RFID 태그를 탐색합니다.

- **Empty** : 일치하는 태그 없음
- **Success** : 태그 1개 식별
- **Collision** : 태그 2개 이상 충돌

충돌이 발생하면 Prefix를 확장하며 탐색을 계속 수행합니다.

## What I Focused On
- 동일한 문제를 재귀 방식과 반복 방식으로 각각 구현
- 탐색 흐름과 결과를 비교할 수 있는 구조 설계
- 탐색 로직과 입력/출력 역할을 분리하여 구조를 정리

## 사용된 설계 패턴

| 패턴 | 적용 위치 | 설명 |
|------|-----------|------|
| Strategy Pattern | `ITagProvider`, `ITagSearcher` | 공통 인터페이스를 기준으로 TAG 생성 방식과 탐색 방식을 교체할 수 있도록 구성했습니다. |
| Simple Factory Pattern | `TagProvider_Factory` | 사용자 입력값에 따라 적절한 `ITagProvider` 구현체를 생성하도록 분리했습니다. |

## Sample Output

실제 콘솔 출력 형식을 기준으로 일부 TAG만 축약한 예시입니다.
```text
=== RFID TAG 입력 방식 선택 ===
1. 정해진 데이터
2. 사용자 직접 입력
3. 랜덤 TAG 생성
1

사전에 정해진 Tag Data 가져옵니다.

========================================
[입력된 TAG 목록]
========================================
1. 0010<TAG 1>
2. 1101<TAG 2>
3. 0011<TAG 3>

========================================
[재귀 방식]
========================================
==== Cycle: 1====
Query: ROOT

Response:0010<TAG 1>
Response:1101<TAG 2>
Response:0011<TAG 3>

Result: Collision

==== Cycle: 2====
Query: 0

Response:0010<TAG 1>
Response:0011<TAG 3>

Result: Collision

==== Cycle: 3====
Query: 000

No matching tags
Result: Empty

==== Cycle: 4====
Query: 0010

Response:0010<TAG 1>

Result: Success

==== Cycle: 5====
Query: 0011

Response:0011<TAG 3>

Result: Success

==== Cycle: 6====
Query: 1

Response:1101<TAG 2>

Result: Success

[탐색 요약]
질의 횟수 : 6
충돌 횟수 : 2
실행 시간 : 19.200 us

[발견된 TAG]
1. 0010<TAG 1>
2. 0011<TAG 3>
3. 1101<TAG 2>

========================================
[반복 방식]
========================================
==== Cycle: 1====
Query: ROOT

Response:0010<TAG 1>
Response:1101<TAG 2>
Response:0011<TAG 3>

Result: Collision

==== Cycle: 2====
Query: 0

Response:0010<TAG 1>
Response:0011<TAG 3>

Result: Collision

==== Cycle: 3====
Query: 000

No matching tags
Result: Empty

==== Cycle: 4====
Query: 0010

Response:0010<TAG 1>

Result: Success

==== Cycle: 5====
Query: 0011

Response:0011<TAG 3>

Result: Success

==== Cycle: 6====
Query: 1

Response:1101<TAG 2>

Result: Success

[탐색 요약]
질의 횟수 : 6
충돌 횟수 : 2
실행 시간 : 7.300 us

[발견된 TAG]
1. 0010<TAG 1>
2. 0011<TAG 3>
3. 1101<TAG 2>

========================================
[비교 결과]
========================================
발견 Tag 동일 여부 : 동일
재귀 방식 질의 횟수 : 6
반복 방식 질의 횟수 : 6
재귀 방식 충돌 횟수 : 2
반복 방식 충돌 횟수 : 2
재귀 방식 실행 시간 : 19.200 us
반복 방식 실행 시간 : 7.300 us
```

## Project Structure

```text
RFIDSearchingSimulator/
├─ RFIDSearchingSimulator.cpp
│  └─ 프로그램 시작점 (main)
│
├─ Function/
│  ├─ StringUtil/
│  │  ├─ Header/
│  │  │  └─ StringUtil.h
│  │  └─ Source/
│  │     └─ StringUtil.cpp
│  │
│  └─ TagSystem/
│     ├─ Interface/
│     │  ├─ ITagProvider.h
│     │  ├─ ITagSearcher.h
│     │  └─ ITagUI.h
│     │
│     ├─ Header/
│     │  ├─ RFIDTag.h
│     │  ├─ TagProvider_Factory.h
│     │  ├─ TagProviderManual.h
│     │  ├─ TagProviderPreset.h
│     │  ├─ TagProviderRandom.h
│     │  ├─ TagSearcherRecursive.h
│     │  ├─ TagSearcherIterative.h
│     │  └─ TagUIConsole.h
│     │
│     └─ Source/
│        ├─ TagProvider_Factory.cpp
│        ├─ TagProviderManual.cpp
│        ├─ TagProviderPreset.cpp
│        ├─ TagProviderRandom.cpp
│        ├─ TagSearcherRecursive.cpp
│        ├─ TagSearcherIterative.cpp
│        └─ TagUIConsole.cpp
```
