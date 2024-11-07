# DSP Assignment-1
Simulation of RC Low-Pass Filter by Discrete Signal Processing

hackmd：https://hackmd.io/@9KvvH16wQKCNkiQnydFUsQ/DSP_Assignment_1

## 學習目標
1. 了解Linear Constant-Coefficient Difference Equation (LCCDE) 的由來以及原理
2. 對於 Sampling Rate 有初步的認識
3. 了解怎麼由連續時間的處理轉變成離散信號的處理
4. 練習以 C 語言撰寫 filter
5. 使用 Python 繪製波形

## **Problem 1**
### **題目**
If $x(t) = e^{j \Omega t}$ ,find $y(t)$ .Nont that $y(t)$ can be expressed by $y(t) = H(\Omega) e^{j \Omega t}$ where $H(\Omega)$ is a function of $\Omega$ with parameters of $R$ and $C$ .

### **解題步驟**
根據題意，假設 $x(t) = e^{j \Omega t}$ ，要找 $y(t)$：
$$
y(t) = H(\Omega) e^{j \Omega t} \tag{1-1}
$$
先求 $H(\Omega)$

由題目的 `eq.(3)` 可以知道：
$$
X(t) = RC \frac{d y(t)}{d t} + y(t) \tag{1-2}
$$

將 $x(t) = e^{j \Omega t}$ 和 $y(t) = H(\Omega) e^{j \Omega t}$ 帶入方程式：
$$
e^{j \Omega t} = RC \frac{d}{dt} \left( H(\Omega) e^{j \Omega t} \right) + H(\Omega) e^{j \Omega t} \tag{1-3}
$$

先求 $\frac{d}{dt} \left( H(\Omega) e^{j \Omega t} \right)$：
$$
\frac{d}{dt} \left( H(\Omega) e^{j \Omega t} \right) = H(\Omega) \cdot j \Omega e^{j \Omega t} \tag{1-4}
$$

再將算出來的 $\frac{d}{dt} \left( H(\Omega) e^{j \Omega t} \right)$ 帶回 `eq.(1-3)` 可以得到：
$$
e^{j \Omega t} = RC \cdot H(\Omega) \cdot j \Omega e^{j \Omega t} + H(\Omega) e^{j \Omega t} \tag{1-5}
$$

因為兩邊都有 $e^{j \Omega t}$，可以消去，最後得到：
$$
1 = (RC \cdot j \Omega + 1) H(\Omega) \tag{1-6}
$$

最後化簡之後可以得到 $H(\Omega)$ ：
$$
H(\Omega) = \frac{1}{RC \cdot j \Omega + 1} \tag{1-7}
$$

帶回 $y(t) = H(\Omega) e^{j \Omega t}$ 得到：
$$
y(t) = \frac{e^{j \Omega t}}{RC \cdot j \Omega + 1} \tag{1-8}
$$
   
---

### 手寫過程
![01](https://hackmd.io/_uploads/ryKEWQYbkl.jpg)

## **Problem 2**
### **題目**
If $x(t) = e^{j\Omega t}u(t)$ , where $u(t)$ is the unit step function, find $y(t)$ .Note that $y(t)$ can be expressed by a transient-state response and a steady-state response.

### **解題步驟**
根據題意，假設 $x(t) = e^{j\Omega t}u(t)$ ，要找 $y(t)$

如果設 $x(t) = \delta(t)$ ，則可以表達為：
$$
\delta(t) = RC \frac{d}{dt}h(t) + h(t) \tag{2-1}
$$

將 `eq.(2-1)` 進行 Laplace Transform $\mathcal{L}\{h(t)\}$ ，假設初始條件為零：
$$
1 = (RC \cdot s + 1) H(s) \tag{2-2}
$$
得到 $H(s)$ ：
$$
H(s) = \frac{1}{RC \cdot s + 1} \tag{2-3}
$$

之後再轉回去 得到 $h(t)$ ：
$$
\mathcal{L}^{-1} \{H(s)\} \Rightarrow h(t) = \frac{1}{RC} e^{-\frac{1}{RC}t} u(t) \tag{2-4}
$$

因為 $y(t) = x(t) * h(t)$ ，則：
$$
y(t) = \int_{0}^{t} h(\tau) e^{j\Omega (t - \tau)} d\tau \tag{2-5}
$$

代入 `eq.(2-4)` 可以得到：
$$
y(t) = \int_{0}^{t} \frac{1}{RC} e^{-\frac{\tau}{RC}} e^{j\Omega (t - \tau)} d\tau \tag{2-6}
$$

可以提出 $e^{j\Omega t}$ 項：
$$
y(t) = \frac{1}{RC} e^{j\Omega t} \int_{0}^{t} e^{-\left(\frac{1}{RC} + j\Omega \right) \tau} d\tau \tag{2-7}
$$

計算積分項，得到 $y(t)$ ：
$$
y(t) = \frac{1}{RC} e^{j\Omega t} \times \frac{1 - e^{-\left(\frac{1}{RC} + j\Omega \right)t}}{\frac{1}{RC} + j\Omega} \tag{2-8}
$$

---

### 手寫過程
![02](https://hackmd.io/_uploads/S1lr-XFb1x.jpg)

## **Problem 3**
### **題目**
If $x(t) = e^{j\Omega t}$ , $R = 1000\Omega$ ,and $C = \left(\frac{1}{2\pi} \times \frac{1}{400} \times \frac{1}{1000}\right)$ ,find $y(t)$ . for $\Omega = 2\pi \cdot f$ , $f = 100\text{Hz}, 400\text{Hz},$ and $3000\text{Hz}$ .

### **解題步驟**
已知
- $R = 1000 \Omega$
- $C = \frac{1}{2\pi \times 400 \times 1000}$
- $y(t) = \frac{e^{j\Omega t}}{RC \cdot j\Omega + 1}$

(1) 當 $f = 100$ Hz時：

計算 $\Omega = 2\pi \cdot f = 2 \pi \times 100 = 200\pi$

$\Omega$ 代入 $(t)$ ：
$$
y(t) = \frac{e^{j200\pi t}}{1000 \cdot \frac{1}{800000\pi} \cdot j200\pi + 1} \tag{3-1}
$$
簡化後得到：
$$
y(t) = \frac{e^{j200\pi t}}{0.25j + 1} \tag{3-2}
$$
$$
y(t) = \frac{4e^{j200\pi t}}{j + 4} \tag{3-3}
$$

(2) 當 $f = 400$ Hz時：

計算 $\Omega = 2\pi \cdot f = 2 \pi \times 400 = 800\pi$

$\Omega$ 代入 $(t)$ ：
$$
y(t) = \frac{e^{j800\pi t}}{1000 \cdot \frac{1}{800000\pi} \cdot j800\pi + 1} \tag{3-4}
$$
簡化後得到：
$$
y(t) = \frac{e^{j800\pi t}}{j + 1} \tag{3-5}
$$

(3) 當 $f = 3000$ Hz時：

計算 $\Omega = 2\pi \cdot f = 2 \pi \times 3000 = 6000\pi$

$\Omega$ 代入 $(t)$ ：
$$
y(t) = \frac{e^{j6000\pi t}}{1000 \cdot \frac{1}{800000\pi} \cdot j6000\pi + 1} \tag{3-6}
$$
簡化後得到：
$$
y(t) = \frac{e^{j6000\pi t}}{7.5j + 1} \tag{3-7}
$$
$$
y(t) = \frac{2e^{j6000\pi t}}{15j + 2} \tag{3-8}
$$

---

### 手寫過程
![03](https://hackmd.io/_uploads/BkqBWmKbyl.jpg)

## **Problem 4**
### **題目**
If $x(t) = e^{j\Omega t}u(t)$ , $R = 1000\Omega$ ,and $C = \left(\frac{1}{2\pi} \times \frac{1}{400} \times \frac{1}{1000}\right)$ ,find $y(t)$ . for $\Omega = 2\pi \cdot f$ , $f = 100\text{Hz}, 400\text{Hz},$ and $3000\text{Hz}$ .

### **解題步驟**
已知
- $R = 1000 \Omega$
- $C = \frac{1}{2\pi \times 400 \times 1000}$
- $y(t) = \frac{1}{RC} e^{j\Omega t} \times \frac{1 - e^{-\left(\frac{1}{RC} + j\Omega\right)t}}{\frac{1}{RC} + j\Omega}$

(1) 當 $f = 100 Hz$ 時：

計算 $\Omega = 2\pi \cdot f = 2 \pi \times 100 = 200\pi$

$\Omega$ 代入 $y(t)$ ：
$$
y(t) = 800\pi e^{j200\pi t} \left( \frac{1 - e^{-(800\pi + j200\pi)t} }{800\pi + 200\pi j}\right) \tag{4-1}
$$
簡化後得到：
$$
y(t) = 4 e^{j200\pi t} \left( \frac{1 - e^{-(800\pi + 200\pi j) t}}{4 + j} \right) \tag{4-2}
$$
$$
y(t) = \frac{4 e^{j200\pi t} - 4 e^{-800\pi t}}{4 + j} \tag{4-3}
$$

(2) 當 $f = 400 Hz$ 時：

計算 $\Omega = 2\pi \cdot f = 2 \pi \times 400 = 800\pi$

$\Omega$ 代入 $y(t)$ ：
$$
y(t) = 800\pi e^{j800\pi t} \left( \frac{1 - e^{-(800\pi + j800\pi)t} }{800\pi + 800\pi j}\right) \tag{4-4}
$$
簡化後得到：
$$
y(t) = e^{j800\pi t} \left( \frac{1 - e^{-(800\pi + 800\pi j) t}}{1 + j} \right) \tag{4-5}
$$
$$
y(t) = \frac{e^{j800\pi t} - e^{-800\pi t}}{1 + j} \tag{4-6}
$$

(3) 當 $f = 3000 Hz$ 時：

計算 $\Omega = 2\pi \cdot f = 2 \pi \times 3000 = 6000\pi$

$\Omega$ 代入 $y(t)$ ：
$$
y(t) = 800\pi e^{j6000\pi t} \left( \frac{1 - e^{-(800\pi + j6000\pi)t} }{800\pi + 6000\pi j}\right) \tag{4-7}
$$
簡化後得到：
$$
y(t) = 2 e^{j6000\pi t} \left( \frac{1 - e^{-(800\pi + 6000\pi j) t}}{2 + 15j} \right) \tag{4-8}
$$
$$
y(t) = \frac{2 e^{j6000\pi t} - 2 e^{-800\pi t}}{2 + 15j} \tag{4-9}
$$

---

### 手寫過程
![04](https://hackmd.io/_uploads/ryGUbXFZ1g.jpg)

## **Problem 5**
### **題目**
If $x[n] = e^{j\omega n}$ , please find the corresponding $y[n] = H(\omega)e^{j\omega n}$ for eq.(8) with sampling rates of 4000Hz, 8000Hz, and 16000Hz.
### **解題步驟**
根據題意，假設 $x(t) = e^{j\Omega t}$ ，則 $y[n] = H(\omega) e^{j\omega n}$

由題目的 `eq.(8)` 可以知道：
$$
y[n] = \frac{RC}{RC + \tau} y[n-1] + \frac{\tau}{\tau + RC} x[n] \tag{5-1}
$$
代入 $x(t)$ , $y(t)$ 得到：
$$
H(\omega) e^{j\omega n} = \frac{RC}{RC + \tau} H(\omega) e^{j\omega(n-1)} + \frac{\tau}{\tau + RC} e^{j\omega n} \tag{5-2}
$$
消掉 $e^{j\omega n}$ ，並將 $H(\omega)$ 項整理到等號右側：
$$
H(\omega) - \frac{RC}{RC + \tau} e^{-j\omega} H(\omega) = \frac{\tau}{\tau + RC} \tag{5-3}
$$
可以得到 $H(\omega)$ ：
$$
H(\omega) = \frac{\frac{\tau}{\tau + RC}}{1 - \frac{RC}{RC + \tau} e^{-j\omega}} \tag{5-4}
$$
作簡化：
$$
H(\omega) = \frac{\tau}{RC + \tau - RC e^{-j\omega}} \tag{5-5}
$$
代回 $y[n] = H(\omega) e^{j\omega n}$ ，得到 $y(t)$ 為：
$$
y[n] = \frac{\tau e^{j\omega n}}{RC + \tau - RC e^{-j\omega}} \tag{5-6}
$$

(1) 當 $fs = 4000 Hz$ 時：
計算 $\tau = \frac{1}{4000}$

代入 $y(t)$
$$
y[n] = \frac{\frac{1}{4000} e^{j\omega n}}{\frac{1}{800\pi} + \frac{1}{4000} - \frac{1}{800\pi} e^{-j\omega}} \tag{5-7}
$$
簡化後：
$$
y[n] = \frac{\pi e^{j\omega n}}{5 + \pi - 5 e^{-j\omega}} \tag{5-8}
$$

(1) 當 $fs = 8000 Hz$ 時：
計算 $\tau = \frac{1}{8000}$

代入 $y(t)$
$$
y[n] = \frac{\frac{1}{8000} e^{j\omega n}}{\frac{1}{800\pi} + \frac{1}{8000} - \frac{1}{800\pi} e^{-j\omega}} \tag{5-8}
$$
簡化後：
$$
y[n] = \frac{\pi e^{j\omega n}}{10 + \pi - 10 e^{-j\omega}} \tag{5-9}
$$

(1) 當 $fs = 16000 Hz$ 時：
計算 $\tau = \frac{1}{16000}$

代入 $y(t)$
$$
y[n] = \frac{\frac{1}{16000} e^{j\omega n}}{\frac{1}{800\pi} + \frac{1}{16000} - \frac{1}{800\pi} e^{-j\omega}} \tag{5-10}
$$
簡化後：
$$
y[n] = \frac{\pi e^{j\omega n}}{20 + \pi - 20 e^{-j\omega}} \tag{5-11}
$$

---

### 手寫過程
![05](https://hackmd.io/_uploads/rkqI-Xt-yg.jpg)

## **Problem 6**
### **題目**
If$x[n] = u[n] e^{j\omega n}$ , please find the corresponding $y[n] = H(\Omega) e^{j\omega n}$ for eq.(8) with sampling rates of 4000Hz, 8000Hz, and 16000Hz.

### **解題步驟**
根據題意，假設 $x[n] = u[n] e^{j\omega n}$ ，則 $y[n] = H(\omega) e^{j\omega n}$

由題目的 `eq.(8)` 可以知道：
$$
y[n] = \frac{RC}{RC + \tau} y[n-1] + \frac{\tau}{\tau + RC} x[n] \tag{6-1}
$$

當 $x[n] = 0$ 時，暫態解為：
$$
y[n] = \frac{RC}{RC + \tau} y[n-1] \tag{6-2}
$$
$$
y[n] = A \left(\frac{RC}{RC + \tau}\right)^n \tag{6-3}
$$
其中 $A$ 是常數

當 $x[n] = e^{j\omega n} u[n]$ 時：
$$
y[n] = \frac{\tau e^{j\omega n}}{RC + \tau - RC e^{-j\omega}} + A \left(\frac{RC}{RC + \tau}\right)^n \tag{6-4}
$$

(1) 當 $fs = 4000 Hz$ 時：
計算 $\tau = \frac{1}{4000}$

代入 $y(t)$
$$
y[n] = \frac{\frac{1}{4000} e^{j\omega n}}{\frac{1}{800\pi} + \frac{1}{4000} - \frac{1}{800\pi} e^{-j\omega}} + A \left(\frac{\frac{1}{800\pi}}{\frac{1}{800\pi} + \frac{1}{4000}}\right)^n \tag{6-5}
$$
簡化後：
$$
y[n] = \frac{\pi e^{j\omega n}}{5 + \pi - 5 e^{-j\omega}} + A \left(\frac{5}{5 + \pi}\right)^n \tag{6-6}
$$

(1) 當 $fs = 8000 Hz$ 時：
計算 $\tau = \frac{1}{8000}$

代入 $y(t)$
$$
y[n] = \frac{\frac{1}{8000} e^{j\omega n}}{\frac{1}{800\pi} + \frac{1}{8000} - \frac{1}{800\pi} e^{-j\omega}} + A \left(\frac{\frac{1}{800\pi}}{\frac{1}{800\pi} + \frac{1}{8000}}\right)^n \tag{6-7}
$$
簡化後：
$$
y[n] = \frac{\pi e^{j\omega n}}{10 + \pi - 10 e^{-j\omega}} + A \left(\frac{10}{10 + \pi}\right)^n \tag{6-8}
$$

(1) 當 $fs = 16000 Hz$ 時：
計算 $\tau = \frac{1}{16000}$

代入 $y(t)$
$$
y[n] = \frac{\frac{1}{16000} e^{j\omega n}}{\frac{1}{800\pi} + \frac{1}{16000} - \frac{1}{800\pi} e^{-j\omega}} + A \left(\frac{\frac{1}{800\pi}}{\frac{1}{800\pi} + \frac{1}{16000}}\right)^n \tag{6-10}
$$
簡化後：
$$
y[n] = \frac{\pi e^{j\omega n}}{20 + \pi - 20 e^{-j\omega}} + A \left(\frac{20}{20 + \pi}\right)^n \tag{6-11}
$$

### 手寫過程
![06](https://hackmd.io/_uploads/HkWP-Xtbkx.jpg)

## **Problem 7**
### **題目**
Simulate the filtering of Problem 4 with `eq.(8)` by C programs. Please discuss the results made by the sampling rates of 4000Hz, 8000Hz, and 16000Hz.
### **程式碼**


