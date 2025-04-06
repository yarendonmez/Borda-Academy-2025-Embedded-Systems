# Borda-Academy-2025-Embedded-Systems
# Borda Academy 2025 – Embedded Systems Developer Ödevi Raporu

**Hazırlayan:** Yaren  
**Tarih:** 06.04.2025

---

## 🔰 1. Proje Amacı

Bu proje, I2C sensörlerden çevresel veri toplayan, bu verileri filtreleyen, istatistiksel olarak işleyen ve BLE üzerinden paylaşan gömülü bir sistem simülasyonunu gerçekleştirmeyi amaçlamaktadır. Gerçek donanım kullanılmaksızın, tüm sistem simüle edilmiştir. Son aşamada, RTOS mimarisi (Producer–Consumer) kullanılarak çoklu görev yapısı uygulanmıştır.

---

## 🔧 2. Sensör Simülasyonu (Mock I2C)

**Amaç:** Gerçek sensör olmadan sıcaklık, nem ve CO₂ gibi verilerin üretimini sağlamak.

**Uygulama:**
- `i2c_sensor_sim.c/.h` dosyalarında `i2c_sensor_read()` fonksiyonu tanımlandı.
- Her sensör türü için mantıklı aralıklarda `float` değer döndürüldü.
- Sensör adresleri:
  - TEMP_SENSOR: `0x48`
  - HUMIDITY_SENSOR: `0x40`
  - CO2_SENSOR: `0x61`

---

## 🧮 3. Medyan Filtreleme

**Amaç:** Aykırı değerleri baskılamak ve daha stabil veri elde etmek.

**Yapılanlar:**
- `median_filter.c/.h` dosyasında `apply_median_filter()` fonksiyonu tanımlandı.
- `qsort` ile sıralama yapılmış, ortadaki değer döndürülmüştür.
- Filtre pencere boyutu gerektiğinde artırılabilir.

---

## 🔁 4. Circular Buffer (Dairesel Tampon)

**Amaç:** Sabit boyutlu veri tamponu ile eski veriyi korurken yenilerini eklemek.

**Detaylar:**
- `circular_buffer.c/.h` dosyasında buffer tanımlandı.
- `push`, `get_all` gibi temel işlemler yazıldı.
- Eğer buffer dolarsa en eski veri üzerine yazılacak şekilde tasarlandı.

---

## 📊 5. İstatistiksel Hesaplama

**Amaç:** BLE paketinde gönderilecek min, max, medyan ve standart sapma hesaplarını yapmak.

**Dosya:** `statistics.c/.h`  
**Fonksiyon:** `calculate_statistics()`

**Hesaplananlar:**
- Minimum
- Maksimum
- Medyan
- Standart sapma (√(toplam fark² / n))

---

## 📡 6. BLE Simülasyonu

**Amaç:** BLE ile gönderilecek verinin yapısını ve zamanlamasını simüle etmek.

**Gerçek Uygulama Yerine:**  
Veriler `printf()` ile konsola basıldı.

**Örnek çıktı:**
```
Sıcaklık -> Min: 21.4 Max: 24.7 Medyan: 23.2 StdDev: 1.1
```

---

## 🧵 7. RTOS Simülasyonu – Producer & Consumer

**Amaç:** Çoklu görev mantığına geçiş yaparak thread tabanlı veri üretim-tüketim akışını sağlamak.

**Gerçek RTOS Yerine:** POSIX `pthread` kütüphanesi ile simülasyon yapılmıştır.

**Dosya:** `rtos_sim.c/.h`

### Yapılanlar:
- Producer thread: 1 saniyede bir sensör verisi üretir.
- Consumer thread: 2 saniyede bir veri tüketir.
- `pthread_mutex_t` ve `pthread_cond_t` ile eşzamanlılık yönetildi.
- Kuyruk dolduğunda veri discard edildi ve loglandı.

---

## 🗂️ 8. Proje Yapısı

```
borda_assignment/
├── sensor_simulation_version/
│   ├── main.c
│   ├── i2c_sensor_sim.c/.h
│   ├── median_filter.c/.h
│   ├── circular_buffer.c/.h
│   ├── statistics.c/.h
├── rtos_version/
│   ├── main.c
│   ├── rtos_sim.c/.h
```

---

## 🗺️ 9. RTOS Akış Diyagramı

- Başla  
  ↓  
- Producer veri üretir  
  ↓  
- Kuyruk dolu mu?  
  - Evetse: logla & veri at  
  - Hayırsa: kuyruğa ekle  
  ↓  
- Consumer kuyruğu kontrol eder  
  ↓  
- Veri varsa alır, yoksa bekler  
  ↓  
- Tüketir ve işlem uygular  
  ↓  
- Bitir

---

## ✅ 10. Sonuç ve Öneriler

Bu simülasyon, donanım olmadan tüm sistem akışını görsel ve mantıksal olarak doğrulamak için oldukça yeterlidir. RTOS mantığı anlaşılmış, çoklu görev yapısı başarıyla uygulanmıştır.  
Geliştirme sonrası gerçek BLE donanımı ile entegrasyon yapılabilir. Aynı yapılar FreeRTOS üzerine taşınabilir.
