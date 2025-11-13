# Graphics pipeline
1. 3D -> 2D
2. 2D -> actual colored pixel

# pipeline paralleism
GPU는 파이프라인의 모든 stage가 동시에 돌아감
```
Stage A: 어떤 정점들을 처리 중
Stage B: 그보다 앞서 처리된 정점들을 primitive assembly 중
Stage C: 더 앞서 처리된 삼각형들을 rasterize 중
Stage D: 더 앞서 만들어진 fragment를 shading 중
Stage E: 완성된 fragment를 depth test 중
```

# Shader
Definition: GPU cores에서 돌아가는 작은 프로그램
- GLSL(OpenGL shading language)로 작성
- CPU와 병렬적으로 동작

# Vertex Shader
주요 목적: 3D coordinate -> different 3D coordinate
- vertex shader의 output은 geometric shader로 넘어감

# Geometric Shader(현재는 잘 안 쓰임)
input: collection of vertices(primitives)
output: new primitives

# Primitive Assembly
input: vertex
output: primitives

# Rasterization
purpose: Map resulting primitives to the corresponding pixels on the final screen

# Clipping
discards fragments outsides our view

# Fragment Shader
Main purpose: calculate final color of a pixel

# Alpha test / blending
Main purpose: checks the corresponding depth value of the fragment and uses those to check if the resulting fragment is in front or behind other objects