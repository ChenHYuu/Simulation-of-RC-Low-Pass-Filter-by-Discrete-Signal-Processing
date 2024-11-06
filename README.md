# DSP Assignment-1
Simulation of RC Low-Pass Filter by Discrete Signal Processing

## 學習目標
1. 了解Linear Constant-Coefficient Difference Equation (LCCDE) 的由來以及原理
2. 對於 Sampling Rate 有初步的認識
3. 了解怎麼由連續時間的處理轉變成離散信號的處理
4. 練習以 C 語言撰寫 filter
5. 使用 Python 繪製波形

## **Problem 1**
### 題目
給定 $x(t) = e^{j \Omega t}$，求 $y(t)$。

根據題意，$y(t)$ 可以表達為：
$$
y(t) = H(\Omega) e^{j \Omega t}
$$
其中 $H(\Omega)$ 是一個與 $\Omega$ 有關的函數，其參數包含 $R$ 和 $C$。
$H(\Omega)$ 是系統的頻率響應函數（傅立葉變換）。

### 解題步驟

1. **假設輸出形態**  
   假設輸出為：
   $$
   y(t) = H(\Omega) e^{j \Omega t}
   $$
   
2. **代入微分方程**  
   根據題意的微分方程式可以得出：
   $$
   X(t) = RC \frac{d y(t)}{d t} + y(t)
   $$
   
3. **將 $y(t) = H(\Omega)e^{j \Omega t}$ 帶入方程**  
   因為 $x(t) = e^{j \Omega t}$，我們將 $y(t) = H(\Omega) e^{j \Omega t}$ 帶入微分方程：
   $$
   e^{j \Omega t} = RC \frac{d}{dt} \left( H(\Omega) e^{j \Omega t} \right) + H(\Omega) e^{j \Omega t}
   $$
   
4. **計算導數項**  
   對 $H(\Omega) e^{j \Omega t}$ 求導數：
   $$
   \frac{d}{dt} \left( H(\Omega) e^{j \Omega t} \right) = H(\Omega) \cdot j \Omega e^{j \Omega t}
   $$
   
5. **代回微分方程**  
   將導數結果代回原方程式：
   $$
   e^{j \Omega t} = RC \cdot H(\Omega) \cdot j \Omega e^{j \Omega t} + H(\Omega) e^{j \Omega t}
   $$
   
6. **提取 $e^{j \Omega t}$ 並化簡**  
   因為兩邊都有 $e^{j \Omega t}$，可以消去，得到：
   $$
   1 = (RC \cdot j \Omega + 1) H(\Omega)
   $$
   
7. **解出 $H(\Omega)$**  
   化簡可得：
   $$
   H(\Omega) = \frac{1}{RC \cdot j \Omega + 1}
   $$
   
8. **最終答案**  
   帶回 $y(t) = H(\Omega) e^{j \Omega t}$ 得到：
   $$
   y(t) = \frac{e^{j \Omega t}}{RC \cdot j \Omega + 1}
   $$
   
---

### 手寫過程
![01](https://hackmd.io/_uploads/ryKEWQYbkl.jpg)

## **Problem 2**

### 手寫過程
![02](https://hackmd.io/_uploads/S1lr-XFb1x.jpg)

## **Problem 3**

### 手寫過程
![03](https://hackmd.io/_uploads/BkqBWmKbyl.jpg)

## **Problem 4**

### 手寫過程
![04](https://hackmd.io/_uploads/ryGUbXFZ1g.jpg)

## **Problem 5**

### 手寫過程
![05](https://hackmd.io/_uploads/rkqI-Xt-yg.jpg)

## **Problem 6**

### 手寫過程
![06](https://hackmd.io/_uploads/HkWP-Xtbkx.jpg)

## **Problem 7**

### 手寫過程

