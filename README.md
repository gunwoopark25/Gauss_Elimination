# Gauss Elimination

C++17로 구현한 **Gauss-Jordan Elimination(가우스-조르당 소거법)** 프로그램입니다.
텍스트 파일로부터 확장 행렬(augmented matrix)을 읽어 선형 연립방정식 $Ax = b$의 해 벡터 $x$를 계산합니다.

---

## 알고리즘

Gauss-Jordan Elimination은 전진 소거(forward elimination)와 후진 소거(backward elimination)를 동시에 수행하여 행렬을 **RREF(Reduced Row Echelon Form, 기약 행 사다리꼴)**로 변환합니다. 이를 통해 별도의 back-substitution 없이 직접 해를 구합니다.

**소거 절차:**

$$\text{For each pivot row } i: \quad R_i \leftarrow \frac{R_i}{a_{ii}}, \quad R_k \leftarrow R_k - a_{ki} \cdot R_i \quad (k \neq i)$$

수렴 결과로 확장 행렬의 우측 열이 곧 해 벡터 $x$가 됩니다.

---

## 프로젝트 구조

```
Gauss_Elimination/
├── Gauss_Elimination.slnx          # Visual Studio solution 파일
└── Gauss_Elimination/
    ├── CMakeLists.txt              # CMake 빌드 설정 (C++17, CLion용)
    ├── Gauss_Elimination.vcxproj   # MSVC 프로젝트 파일
    ├── Matrix.h                    # Matrix 클래스 선언
    ├── Matrix.cpp                  # Matrix 클래스 구현 (핵심 로직)
    ├── main.cpp                    # 진입점
    ├── Gauss_3.txt                 # 샘플 입력 — 3×3 연립방정식
    └── Gauss_4.txt                 # 샘플 입력 — 4×4 연립방정식 (기본 활성)
```

---

## 소스 파일 설명

### `Matrix.h`
`Matrix` 클래스를 선언합니다.

| 멤버 | 설명 |
|------|------|
| `int Size` | 연립방정식의 미지수 개수 (행렬 크기 n) |
| `double** matrix` | 동적 할당된 n × (n+1) 확장 행렬 |
| `double Set` | 피벗 정규화 시 사용하는 pivot 값 |
| `double factor` | 행 소거 시 사용하는 배율 인수 |
| `fileLoad()` | 텍스트 파일로부터 행렬 읽기 |
| `calulate()` | Gauss-Jordan 소거 수행 |
| `loadFinalinversematrix()` | 해 벡터를 콘솔에 출력 |
| `writeFile()` | 해 벡터를 결과 파일에 저장 |

### `Matrix.cpp`
- **생성자**: `fileLoad()` 호출 → `Gauss_4.txt` 로부터 행렬 로드
- **소멸자**: `writeFile()` 호출 → 결과를 `Gauss_4_ans.txt`에 자동 저장
- **`calulate()`**: 핵심 알고리즘. 각 pivot 행을 정규화한 뒤, 해당 열의 나머지 행 원소를 소거

### `main.cpp`
```cpp
Matrix matrix3;           // 생성자에서 파일 로드
matrix3.calulate();       // Gauss-Jordan 소거 수행
matrix3.loadFinalinversematrix();  // 콘솔 출력
// 소멸자에서 자동으로 결과 파일 저장
```

---

## 입력 파일 형식

첫 번째 줄에 행렬 크기 `n`, 이후 `n`개의 행에 확장 행렬 `[A | b]`를 공백으로 구분하여 입력합니다.

**예시 — `Gauss_4.txt` (4×4 연립방정식):**
```
4
 1  2  1  1  -3
 3 -1 -1  2   5
 2  3 -1 -3  -9
-2  6 -5  2   1
```

이는 다음 연립방정식에 해당합니다:

$$\begin{cases} x_1 + 2x_2 + x_3 + x_4 = -3 \\ 3x_1 - x_2 - x_3 + 2x_4 = 5 \\ 2x_1 + 3x_2 - x_3 - 3x_4 = -9 \\ -2x_1 + 6x_2 - 5x_3 + 2x_4 = 1 \end{cases}$$

---

## 출력

- **콘솔**: 해 벡터 $x = [x_1, x_2, \ldots, x_n]$ 출력
- **파일**: 실행 디렉토리에 `Gauss_4_ans.txt` 생성

---

## 빌드 방법

### CMake (CLion / Linux / macOS)
```bash
cd Gauss_Elimination
mkdir cmake-build-debug && cd cmake-build-debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
./Gauss_Elimination
```
> 실행 시 입력 파일(`Gauss_4.txt`)이 **실행 디렉토리**에 있어야 합니다.

### Visual Studio (Windows)
`Gauss_Elimination.slnx`를 Visual Studio에서 열고 빌드합니다.
입력 파일은 `.vcxproj`와 동일한 디렉토리에 위치해야 합니다.

---

## 주의 사항

- **Partial Pivoting(부분 피벗팅) 미적용**: pivot 원소가 0이면 division by zero가 발생합니다. 입력 행렬은 적절한 행 순서로 정렬되어 있어야 합니다.
- **입력 파일 경로 하드코딩**: `fileLoad()` 내부에서 `"Gauss_4.txt"`를 직접 참조합니다. 다른 파일을 사용하려면 소스 코드를 수정해야 합니다.
- **메모리 해제**: 동적 할당된 `matrix`에 대한 명시적 `delete` 코드가 없으므로, 대규모 행렬 사용 시 메모리 누수에 유의하십시오.
