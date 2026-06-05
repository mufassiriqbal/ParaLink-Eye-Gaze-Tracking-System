# ParaLink — EOG Communication System for Paralyzed Individuals

A full-stack assistive communication application designed for paralyzed patients using **Electrooculography (EOG)** technology. The system enables users to communicate, control home appliances, read news, and send emergency alerts entirely through eye blinks — without any physical interaction.

## Project Overview

**ParaLink** is a Final Year Project (FYP) that bridges the communication gap for individuals with severe motor disabilities. It uses EOG signals (detected via a webcam using MediaPipe FaceLandmarker, or simulated via keyboard) to let patients navigate a touch-free digital interface. All selections are made by blinking 3 times on a focused element, and 2 blinks close or go back.

The system consists of:
- A **React frontend** served via Vite
- A **Python FastAPI backend** that handles TTS (gTTS), IoT device control via ESP32, and selection history

---

## Key Features

### Authentication
- Secure email/password login and signup via **Supabase**
- Animated welcome screen shown once per session

### Dashboard — Category Cards
- **Communication** — Express emotions/needs via selectable cards with multilingual text-to-speech
- **News** — Browse health, tech, world news, and trending articles by category
- **Home Appliances** — Control lights, fan, TV, AC, and WiFi router via ESP32 (GPIO-based relay)
- **Emergency** — One-blink-to-alert for nurse, medication, medical alert, and emergency services

### EOG Blink Detection
- **Keyboard Mode** — Spacebar simulates blinks (for demo/testing)
- **WebCam Mode** — Real-time eye tracking using browser-based MediaPipe FaceLandmarker (no Python needed for tracking)
- Blink counter displayed live on focused element (e.g. `2/3`)

### Text-to-Speech (3-Layer Fallback)
1. **Backend gTTS** (`http://localhost:8000/tts`) — Best quality
2. **Browser SpeechSynthesis** — Instant, used if voice is available
3. **Google Translate TTS** — Reliable fallback for Urdu, Arabic, and all supported languages

### Multi-Language Support
Supports 6 languages: English, Urdu, Arabic, Spanish, French, German  
Language preference is persisted in `localStorage`.

### Home Appliance Control (IoT)
- Communicates with ESP32 microcontroller via Python serial relay
- Devices: Lights (GPIO 23), Fan (GPIO 22), TV (GPIO 21), AC (GPIO 19), WiFi Router
- Live device status polling every 5 seconds
- Commands sent to `POST /select` with `type: "device"`

---

## Technology Stack

### Frontend
| Technology | Version | Purpose |
|---|---|---|
| React | 18.3.1 | UI framework |
| Vite | 5.4.2 | Build tool & dev server |
| Tailwind CSS | 3.4.1 | Utility-first styling |
| Lucide React | 0.344.0 | Icon library |
| Bootstrap / React-Bootstrap | 5.3.x | Additional UI components |

> **Note:** The frontend is written in **JavaScript (JSX)**, not TypeScript.

### Backend
| Technology | Purpose |
|---|---|
| Python FastAPI | REST API server on `http://localhost:8000` |
| gTTS (Google TTS) | Text-to-speech audio generation |
| PySerial | Serial communication with ESP32 |
| Supabase (Python) | Optional data persistence |

### Authentication & Database
- **Supabase** — Auth (email/password) and optional data storage
- Credentials stored in `.env` (not committed to version control)

### Browser APIs Used
- **MediaPipe FaceLandmarker** (WASM) — Real-time eye tracking in the browser
- **Web Speech API** — Browser TTS fallback
- **SpeechSynthesis** — Multilingual voice output

---

## Prerequisites

- **Node.js** v18 or higher
- **npm** package manager
- **Python 3.9+** (for backend)
- A **Supabase** account (for authentication)
- **ESP32** microcontroller (optional, for real appliance control)

---

## Installation & Setup

### 1. Clone the repository

```bash
git clone https://github.com/syedAli124944/ParaLink-Eye-Gaze-Tracking-System.git
cd ParaLink-Eye-Gaze-Tracking-System
```

### 2. Frontend Setup

```bash
cd FYP_EOG_System_For_Paralyzed_people
npm install
```

Create a `.env` file in `FYP_EOG_System_For_Paralyzed_people/`:

```env
VITE_SUPABASE_URL=your-supabase-project-url
VITE_SUPABASE_ANON_KEY=your-supabase-anon-key
```

### 3. Backend Setup

```bash
cd ../backend
python -m venv .venv
.venv\Scripts\activate        # Windows
pip install -r requirements.txt
```

### 4. Run the Application

**Start the backend** (in the `backend/` directory):
```bash
python main.py
```
The backend will be available at `http://localhost:8000`.

**Start the frontend** (in the `FYP_EOG_System_For_Paralyzed_people/` directory):
```bash
npm run dev
```
The frontend will be available at `http://localhost:5173` (or `5174` if port is in use).

---

## Usage

### EOG Interaction
- **3 blinks** — Select the focused/highlighted element
- **2 blinks** — Go back / close the current modal
- Gaze at an element to focus it; a blink counter (`x/3`) appears on the focused item

### EOG Mode Selection (Sidebar)
1. Enable **EOG Mode** toggle in the sidebar
2. Choose **Keyboard (Spacebar)** for demo/testing, or **WebCam Tracking** for real eye tracking

### Language Selection
Select a language from the **Voice Language** dropdown in the sidebar. All TTS output will be in the selected language.

---

## Project Structure

```
ParaLink-Eye-Gaze-Tracking-System/
├── FYP_EOG_System_For_Paralyzed_people/   # React Frontend
│   ├── src/
│   │   ├── components/
│   │   │   ├── Dashboard.jsx              # Main dashboard + Contact/About pages
│   │   │   ├── CommunicationModal.jsx     # Emotion expression cards
│   │   │   ├── NewsModal.jsx              # News categories and articles
│   │   │   ├── HomeAppliancesModal.jsx    # IoT device control panel
│   │   │   ├── EmergencyModal.jsx         # Emergency alert buttons
│   │   │   ├── Sidebar.jsx                # Navigation + EOG/language controls
│   │   │   ├── Login.jsx                  # Login page
│   │   │   ├── SignUp.jsx                 # Signup page
│   │   │   ├── WelcomeScreen.jsx          # Animated welcome screen
│   │   │   ├── BlinkIndicator.jsx         # Blink count HUD
│   │   │   ├── GazeCursor.jsx             # Visual gaze cursor overlay
│   │   │   └── WebcamPreview.jsx          # Webcam feed (hidden when not needed)
│   │   ├── contexts/
│   │   │   ├── AuthContext.jsx            # Supabase auth state
│   │   │   └── EogContext.jsx             # EOG mode, language, blink state
│   │   ├── hooks/
│   │   │   ├── useEogSelection.js         # Per-element EOG focus + blink hook
│   │   │   └── useDoubleBlink.js          # Double-blink (back/close) hook
│   │   ├── services/
│   │   │   ├── EogService.js              # Core blink detection (keyboard & webcam)
│   │   │   ├── BrowserEyeTracker.js       # MediaPipe FaceLandmarker integration
│   │   │   ├── TtsService.js              # 3-layer TTS fallback service
│   │   │   └── ApiService.js              # Backend API communication
│   │   ├── App.jsx                        # App root + auth routing
│   │   ├── main.jsx                       # React entry point
│   │   └── index.css                      # Global styles + Tailwind directives
│   ├── public/                            # Static assets
│   ├── index.html                         # HTML entry point
│   ├── vite.config.js                     # Vite configuration
│   ├── tailwind.config.js                 # Tailwind configuration
│   └── package.json                       # Frontend dependencies
│
└── backend/                               # Python FastAPI Backend
    ├── main.py                            # FastAPI app entry point
    ├── services/
    │   ├── serial_service.py              # ESP32 serial communication
    │   └── iot_service.py                 # IoT device command handling
    └── requirements.txt                   # Python dependencies
```

---

## Design Philosophy

ParaLink is designed with **accessibility as the primary constraint**:

- **Large touch targets** — All interactive elements are sized for eye-based selection
- **High contrast gradients** — Distinct color coding per module for quick visual recognition
- **Minimal cognitive load** — Flat navigation, no nested menus beyond 2 levels
- **Calm color palette** — Teal/cyan primary tones reduce visual fatigue for long-term use
- **Responsive layout** — Works on desktop and tablet screens

---

## Backend API Reference

| Endpoint | Method | Description |
|---|---|---|
| `/health` | GET | Check if backend is running |
| `/select` | POST | Send a user selection (communication/device/emergency) |
| `/tts` | POST | Generate and return a TTS audio file |
| `/devices/status` | GET | Get current IoT device states |
| `/history` | GET | Get recent selection history |
| `/suggestions` | GET | Get smart suggestions based on usage |

**POST /select** body:
```json
{
  "type": "communication | device | emergency",
  "value": "hungry | light_on | nurse | ...",
  "language": "en | ur | ar | es | fr | de"
}
```

---

## Security

- Supabase handles all authentication; credentials are never stored client-side
- `.env` file is git-ignored; never committed
- Session tokens are managed automatically by the Supabase client SDK

---

## License

This project is submitted as a Final Year Project (FYP) for academic evaluation. Intended for educational and research purposes.

## Authors

**FYP Team — ParaLink EOG Communication System**  
Department of Computer Science  
COMSATS University Islamabad, Abbottabad Campus

---

*For questions or issues, use the GitHub Issues tracker.*
