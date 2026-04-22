# RFID Collision Search Simulator
**C++ Console Project for Comparing Recursive and Iterative RFID Search**

Prefix 기반 질의 방식으로 RFID TAG 충돌 탐색 과정을 시뮬레이션하고,  
동일한 TAG 집합에 대해 **재귀 방식**과 **반복 방식**의 탐색 흐름 및 결과를 비교한 C++ 콘솔 프로젝트입니다.

---

## Overview
이 프로젝트는 RFID 환경에서 발생할 수 있는 **TAG 충돌 탐색 과정**을 콘솔 환경에서 재현한 시뮬레이터입니다.  
사용자는 TAG 입력 방식을 선택할 수 있으며, 프로그램은 동일한 TAG 집합에 대해 다음 두 가지 탐색 전략을 수행합니다.

- **Recursive Search**
- **Iterative Search (Stack-based)**

각 방식에 대해 질의 로그, 탐색 결과, 충돌 횟수, 실행 시간을 출력하고,  
최종적으로 두 구현 방식의 결과를 비교할 수 있도록 설계했습니다.

---

## Tech Stack
- **Language**: C++
- **IDE / Toolchain**: Visual Studio 2022
- **Platform Toolset**: MSVC v143
- **Project Type**: Windows Console Application

---

## Key Features
- **Preset / Manual / Random** 방식의 TAG 입력 지원
- **4bit RFID TAG 충돌 탐색** 시뮬레이션
- **재귀 탐색 / 반복 탐색** 방식 비교
- 질의별 **Cycle / Prefix / Response / Result** 로그 출력
- 발견된 TAG, 질의 횟수, 충돌 횟수, 실행 시간 요약 제공
- TAG를 `0010<TAG 1>` 형식으로 출력하여 식별 가능

---

## Input Rules
- 모든 TAG는 **4bit 이진 문자열**이어야 합니다. (`0000 ~ 1111`)
- **중복 TAG는 허용되지 않습니다.**
- TAG는 입력/생성 순서대로 ID가 부여됩니다.

예시:
- `0010<TAG 1>`
- `1101<TAG 2>`
- `0011<TAG 3>`

---

## Search Model
이 프로젝트는 **Prefix 기반 RFID 충돌 탐색 모델**을 사용합니다.

특정 질의 prefix가 주어졌을 때, 해당 prefix로 시작하는 TAG들을 응답 대상으로 간주합니다.  
탐색 결과는 다음 세 가지 상태로 구분됩니다.

- `Empty` : 일치하는 TAG 없음
- `Success` : 정확히 1개의 TAG만 일치
- `Collision` : 2개 이상의 TAG가 동시에 일치

충돌이 발생하면 prefix를 더 세분화하여 다음 단계로 탐색합니다.

예:
- `""` → `"0"`, `"1"`
- `"0"` → `"00"`, `"01"`

이 과정을 반복해 최종적으로 모든 TAG를 개별적으로 식별합니다.

---

## Design Highlights
### 1. Interface-based Design
역할을 인터페이스 단위로 분리해 **구현 교체와 확장성**을 고려했습니다.

- `ITagProvider` : TAG 생성 방식 추상화
- `ITagSearcher` : 탐색 알고리즘 추상화
- `ITagUI` : 사용자 입출력 추상화

### 2. Search Strategy Comparison
동일한 TAG 집합에 대해 아래 두 방식을 각각 수행합니다.

- **Recursive prefix expansion**
- **Iterative stack-based traversal**

이를 통해 같은 문제를 서로 다른 방식으로 구현하고,  
탐색 흐름과 결과를 비교할 수 있도록 구성했습니다.

### 3. Applied Patterns
- **Strategy Pattern**  
  `ITagProvider`, `ITagSearcher`를 기반으로 TAG 생성 방식과 탐색 방식을 교체 가능하게 설계했습니다.

- **Factory Pattern**  
  `TagProvider_Factory`를 통해 사용자 입력에 따라 적절한 Provider 구현체를 생성하도록 분리했습니다.

---

## Why This Project Matters
이 프로젝트는 단순한 콘솔 프로그램 구현이 아니라, 다음 역량을 보여주는 데 초점을 맞췄습니다.

- **객체지향 설계 능력**
- **인터페이스 기반 구조 설계 경험**
- **동일 문제를 재귀 / 반복 방식으로 비교 구현한 경험**
- **출력 결과를 통해 동작 과정을 명확히 보여주는 로깅 설계**

즉, 기능 구현뿐 아니라 **설계 분리, 확장성, 비교 가능한 구조**를 고민한 프로젝트입니다.

---

## Sample Output
```text
========================================
[입력된 TAG 목록]
========================================
1. 0010<TAG 1>
2. 1101<TAG 2>
3. 0011<TAG 3>

========================================
[Iterative Search]
========================================
==== Cycle: 1 ====
Query: ROOT

Response: 0010<TAG 1>
Response: 0011<TAG 3>

Result: Collision
```

일치하는 TAG가 없는 경우:

```text
No matching tags
```

---

## Project Structure
> Visual Studio Filter 기준으로 논리적으로 분류한 구조입니다.

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

### Structure Notes
- **Interface**  
  Provider / Searcher / UI 역할을 추상화한 계층

- **Header**  
  데이터 모델 및 구체 구현체 선언부

- **Source**  
  실제 동작 로직 구현부

- **StringUtil**  
  문자열 처리 관련 공통 유틸리티 분리

---

## How to Run
1. `RFIDSearchingSimulator.sln`을 Visual Studio 2022에서 엽니다.
2. `Debug` 또는 `Release` 구성을 선택합니다.
3. 빌드 후 실행합니다.
4. 콘솔에서 TAG 입력 방식을 선택합니다.

---

## What I Focused On
- 동일한 문제를 **재귀 / 반복 두 방식으로 구현하고 비교**한 점
- **역할 분리와 확장 가능성**을 고려한 객체지향 구조
- 콘솔 기반 프로젝트에서도 **명확한 흐름과 결과 출력**을 제공한 점

---

## Limitations
- 현재는 **4bit 이진 TAG**만 지원합니다.
- **중복 TAG**는 허용되지 않습니다.
- **콘솔 UI** 기반으로만 동작합니다.
- 실제 RFID 하드웨어와 연동하지 않는 **시뮬레이션 프로젝트**입니다.