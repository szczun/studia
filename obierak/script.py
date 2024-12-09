from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time

# Ustawienia
USOS_URL = "https://www.youtube.com/"  # Strona YouTube
SEARCH_QUERY = "Python tutorial"  # Zapytanie do wyszukania

# Uruchomienie przeglądarki z wyłączoną akceleracją GPU
options = webdriver.ChromeOptions()
options.add_argument('--disable-gpu')  # Wyłączenie akceleracji GPU
driver = webdriver.Chrome(options=options)  # Można użyć Firefox, jeśli preferujesz

try:
    # Otwórz stronę YouTube
    driver.get(USOS_URL)

    # Poczekaj na załadowanie elementu wyszukiwania
    search_box = WebDriverWait(driver, 20).until(
        EC.element_to_be_clickable((By.NAME, "search_query"))
    )
    
    # Wpisz zapytanie do wyszukiwarki
    search_box.send_keys(SEARCH_QUERY)
    search_box.send_keys(Keys.RETURN)  # Naciśnij Enter, aby wyszukać
    
    # Poczekaj na załadowanie wyników wyszukiwania
    WebDriverWait(driver, 20).until(
        EC.presence_of_element_located((By.ID, "video-title"))
    )
    
    # Kliknij na pierwszy wynik
    first_video = driver.find_element(By.ID, "video-title")
    
    # Upewnij się, że element jest widoczny i klikniesz na niego
    driver.execute_script("arguments[0].scrollIntoView(true);", first_video)
    first_video.click()
    
    # Poczekaj na załadowanie strony z filmem
    WebDriverWait(driver, 15).until(
        EC.presence_of_element_located((By.CSS_SELECTOR, "button.ytp-play-button"))
    )
    
    # Po kliknięciu na film, poczekaj chwilę, aby odtworzyć
    time.sleep(5)  # Odczekaj 5 sekund na rozpoczęcie odtwarzania
    
    # Możesz dodać dodatkowe akcje, np. zatrzymać film po chwili
    driver.find_element(By.CSS_SELECTOR, "button.ytp-play-button").click()  # Kliknij pauzę

    print("Film został odtworzony i zatrzymany.")
    
except Exception as e:
    print("Wystąpił błąd:", e)
finally:
    driver.quit()
