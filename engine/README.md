# Engine

Engine, C++ ile geliştirilmiş, temel oyun ve grafik uygulamaları için tasarlanmış modüler bir oyun motorudur. Modern C++ standartlarını ve endüstri standardı kütüphaneleri kullanır. 

## Özellikler
- **Modüler mimari**: Kolayca genişletilebilir ve özelleştirilebilir yapı.
- **Shader ve Texture yönetimi**: GLSL tabanlı shader ve temel doku yönetimi.
- **Çarpışma Algoritması**: Basit çarpışma tespiti.
- **Zamanlayıcı ve Profil Aracı**: Performans ölçümü ve zaman yönetimi.
- **GLM, stb_image, GLAD** gibi popüler açık kaynak kütüphaneler ile entegrasyon.

## Klasör Yapısı
- `src/` : Motorun ana kaynak kodları
- `include/` : Başlık dosyaları
- `external/` : Harici kütüphaneler
- `assets/` : Shader ve doku dosyaları
- `build/` : Derleme çıktıları
- `sandbox/` : Örnek uygulama

## Derleme
Proje, CMake ile yapılandırılmıştır. Derlemek için:

```sh
mkdir build
cd build
cmake ..
ninja
```

Alternatif olarak, CMake ile farklı derleyiciler de kullanılabilir.

## Bağımlılıklar
- [GLM](https://github.com/g-truc/glm)
- [stb_image](https://github.com/nothings/stb)
- [GLAD](https://github.com/Dav1dde/glad)
- OpenGL (geliştirici sisteminde kurulu olmalıdır)

## Kullanım
Derleme sonrası `engine.exe` ve örnek uygulama olarak `sandbox.exe` çalıştırılabilir. Shader ve doku dosyaları `assets/` klasöründe bulunur.

## Katkı
Katkıda bulunmak için lütfen bir pull request açın veya issue oluşturun. Kod standartlarına ve mevcut mimariye uygun geliştirme yapınız.

## Lisans
Bu proje MIT lisansı ile lisanslanmıştır.
