# StyleTransferNet: A Lightweight Neural Architecture for Real-Time Artistic Style Transfer

**Author:** Jane Doe  
**Affiliation:** Department of Computer Science, University of Example  
**Email:** jane.doe@example.edu  
**Date:** May 17, 2025

<span style="color : 564789;"><strong>Address: </strong>
Bangalore
<span>

---

<details>
<summary><strong>Abstract</strong></summary>

We present *StyleTransferNet*, a lightweight convolutional neural network designed for fast and high-quality artistic style transfer. Unlike traditional optimization-based methods, our approach enables real-time transformation of images while preserving key semantic content and stylistic features. Through quantitative benchmarks and visual comparisons, we demonstrate that StyleTransferNet achieves state-of-the-art results with significantly lower computational cost.

</details>

---

<details>
<summary><strong>1. Introduction</strong></summary>

Artistic style transfer refers to the process of applying the visual appearance (style) of one image to the semantic content of another. First introduced by Gatys et al. (2015), the technique has since evolved into real-time models using feed-forward networks.

However, existing methods often face trade-offs between speed, quality, and model size. Our work introduces **StyleTransferNet**, which builds on residual learning and attention mechanisms to provide efficient and flexible style transfer with minimal resource demands.

</details>

---

<details>
<summary><strong>2. Related Work</strong></summary>

- **Gatys et al. (2015):** Optimization-based style transfer using VGG-19 features.
- **Johnson et al. (2016):** Fast style transfer via feed-forward networks.
- **Huang and Belongie (2017):** Adaptive instance normalization for arbitrary styles.

While these approaches laid the groundwork, they either require heavy computation or limit the range of stylization. Our method aims to strike a balance.

</details>

---

<details>
<summary><strong>3. Methodology</strong></summary>

### 3.1 Network Architecture

Our architecture consists of:

- An encoder (based on a truncated VGG-16).
- A stylization bottleneck with attention modules.
- A decoder with skip connections to retain high-frequency details.

We use **instance normalization** and **residual blocks** to ensure stable training and stylized consistency.

### 3.2 Loss Functions

We optimize the model using a weighted sum of:

- **Content Loss**: MSE between deep features of the output and content image.
- **Style Loss**: Gram matrix distance from the target style.
- **Total Variation Loss**: Regularizes spatial smoothness.

</details>

---

<details>
<summary><strong>4. Experiments</strong></summary>

### 4.1 Datasets

- **Content images**: MS-COCO 2014.
- **Style images**: Curated set of 20 classical artworks.

### 4.2 Evaluation Metrics

| Metric         | StyleTransferNet | Johnson et al. | AdaIN |
|----------------|------------------|----------------|-------|
| PSNR (↑)       | 26.5             | 25.8           | 24.3  |
| Style Loss (↓) | 1.13             | 1.45           | 1.21  |
| FPS (↑)        | 48               | 32             | 27    |

### 4.3 Visual Results

![Stylized Samples](figures/style_samples.png)

_Our method preserves both fine textures and global structure._

</details>

---

<details>
<summary><strong>5. Conclusion</strong></summary>

We introduced StyleTransferNet, a real-time and lightweight model for high-quality artistic style transfer. Our method achieves competitive results with significantly improved efficiency, making it suitable for deployment on mobile and edge devices.

Future work includes extending the model to support video stylization and user-controllable style blending.

</details>

---

<details>
<summary><strong>References</strong></summary>

1. Gatys, L. A., Ecker, A. S., & Bethge, M. (2015). A Neural Algorithm of Artistic Style. *arXiv preprint arXiv:1508.06576*  
2. Johnson, J., Alahi, A., & Fei-Fei, L. (2016). Perceptual Losses for Real-Time Style Transfer and Super-Resolution. *ECCV*  
3. Huang, X., & Belongie, S. (2017). Arbitrary Style Transfer in Real-Time with Adaptive Instance Normalization. *ICCV*

</details>
