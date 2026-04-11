from playwright.sync_api import sync_playwright
import time

PHONE = "9999999999"

SITES = [
    "https://www.jeep-india.com/shopping_tools/satd.new-jeep-meridian.html?utm_source=Google&utm_medium=CPC&utm_campaign=meridianbrand_broad_april25&gclsrc=aw.ds&gad_source=1&gad_campaignid=22459474707&gbraid=0AAAAADSDigiRzsslte3xszOLyP_oq53UL&gclid=EAIaIQobChMI7oKvpPfMkwMVqqRmAh1L7SWfEAAYASAAEgJ2dvD_BwE",
    "https://www.jeep-india.com/shopping_tools/satd.new-jeep-meridian.html?utm_source=Google&utm_medium=CPC&utm_campaign=meridianbrand_broad_april25&gclsrc=aw.ds&gad_source=1&gad_campaignid=22459474707&gbraid=0AAAAADSDigiRzsslte3xszOLyP_oq53UL&gclid=EAIaIQobChMI7oKvpPfMkwMVqqRmAh1L7SWfEAAYASAAEgJ2dvD_BwE",
]


def safe_get_attr(element, attr):
    try:
        val = element.get_attribute(attr)
        return val if val else ""
    except:
        return ""


def find_phone_input(page):
    inputs = page.query_selector_all("input")

    for inp in inputs:
        attrs = " ".join([
            safe_get_attr(inp, "placeholder"),
            safe_get_attr(inp, "name"),
            safe_get_attr(inp, "id"),
            safe_get_attr(inp, "type")
        ]).lower()

        if any(k in attrs for k in ["phone", "mobile", "tel"]):
            return inp

    return None


def fill_other_inputs(page):
    inputs = page.query_selector_all("input")

    for inp in inputs:
        try:
            t = safe_get_attr(inp, "type").lower()
            attrs = " ".join([
                safe_get_attr(inp, "placeholder"),
                safe_get_attr(inp, "name")
            ]).lower()

            if any(k in attrs for k in ["phone", "mobile"]):
                continue

            if t in ["text", "email"]:
                inp.fill("test@example.com")
            elif t == "password":
                inp.fill("Test@1234")
            elif t == "number":
                inp.fill("123456")

        except:
            continue


def click_submit(page):
    buttons = page.query_selector_all("button, input[type=submit]")

    for btn in buttons:
        try:
            text = (btn.inner_text() or "").lower()

            if any(k in text for k in ["login", "sign", "otp", "continue", "next"]):
                btn.click()
                return True
        except:
            continue

    # fallback
    if buttons:
        try:
            buttons[0].click()
            return True
        except:
            pass

    return False


def handle_otp(page):
    print("Waiting for OTP...")
    time.sleep(20)

    inputs = page.query_selector_all("input")

    for inp in inputs:
        attrs = " ".join([
            safe_get_attr(inp, "placeholder"),
            safe_get_attr(inp, "name")
        ]).lower()

        if "otp" in attrs:
            try:
                otp = input("Enter OTP: ")
                inp.fill(otp)
                print("OTP entered")
                return
            except:
                pass


def run(site):
    print("\n--- Testing:", site, "---")

    with sync_playwright() as p:
        browser = p.chromium.launch(headless=False)
        page = browser.new_page()

        try:
            page.goto(site, timeout=60000)
        except:
            print("Failed to load page")
            return

        time.sleep(5)

        fill_other_inputs(page)

        phone_input = find_phone_input(page)

        if phone_input:
            try:
                phone_input.fill(PHONE)
                print("Phone filled")
            except:
                print("Failed to fill phone")
        else:
            print("Phone input not found")

        if click_submit(page):
            print("Clicked submit")
        else:
            print("Submit button not found")

        handle_otp(page)

        time.sleep(5)
        browser.close()


if __name__ == "__main__":
    for site in SITES:
        try:
            run(site)
        except Exception as e:
            print("Error:", e)