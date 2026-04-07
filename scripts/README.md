# Scripts

## Planned

**`uart_smoke.py`** - Open the ST-Link VCP, wait for **`BOOT`**, send **`start`**, count **`TLM`** lines in a time window, and exit non-zero on failure.

## Setup

```text
cd scripts
python -m venv .venv
pip install pyserial
```

Pass **COM port** (Windows) or **`/dev/tty.*`** (Unix) as a CLI flag. This remains optional helper work; no host-side smoke script is committed yet.
