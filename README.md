# RFID Collision Search Simulator

재귀 방식과 반복 방식의 RFID 태그 충돌 탐색 과정을 비교하기 위해 구현한 C++ 콘솔 프로젝트입니다.

## Tech Stack
- C++
- STL

## Features
- Prefix 기반 RFID 태그 충돌 탐색 시뮬레이션
- 재귀 방식과 반복 방식 비교
- 질의 횟수, 충돌 횟수, 실행 시간 비교
- Preset / Manual / Random 입력 방식 지원

## Search Model
Prefix 기반 질의를 통해 태그를 탐색합니다.

- **Empty** : 일치하는 태그 없음
- **Success** : 태그 1개 식별
- **Collision** : 태그 2개 이상 충돌

충돌이 발생하면 Prefix를 확장하며 탐색을 계속 수행합니다.

## What I Focused On
- 동일한 문제를 재귀 방식과 반복 방식으로 각각 구현
- 탐색 흐름과 결과를 비교할 수 있는 구조 설계
- 탐색 로직과 입력/출력 역할을 분리하여 구조를 정리

## Sample Output
<img width="332" height="270" alt="image" src="https://github.com/user-attachments/assets/e91d0fb5-7494-4f74-9938-85c4cd879f86" />
<img width="330" height="818" alt="image" src="https://github.com/user-attachments/assets/e4a87871-b320-4f96-a57c-34dd2fc28af8" />
