import json
import glob
from pathlib import Path
from vlm_client import analyze_image
from prompt import prompts
from schema import PartTemplate

INPUT_DIR = "phase1_inputs"
OUTPUT_DIR = "outputs/phase1_templates"

Path(OUTPUT_DIR).mkdir(parents=True, exist_ok=True)

SYSTEM_PROMPT, USER_PROMPT = prompts()
PROMPT = SYSTEM_PROMPT + "\n\n" + USER_PROMPT

image_paths = glob.glob(f"{INPUT_DIR}/*.png")

if not image_paths:
    raise RuntimeError("No images found in phase1 input directory")

for img_path in image_paths:
    print(f"\n[INFO] Processing {img_path}")

    raw_text = analyze_image(img_path, PROMPT)

    print("---- RAW VLM OUTPUT ----")
    print(raw_text)
    print("------------------------")

    try:
        data = json.loads(raw_text)
    except json.JSONDecodeError as e:
        print("[ERROR] VLM output is not valid JSON")
        print(e)
        print("[SKIP] File not saved")
        continue

    try:
        template = PartTemplate(**data)
    except Exception as e:
        print("[ERROR] VLM output does not match schema")
        print(e)
        print("[SKIP] File not saved")
        continue

    out_path = Path(OUTPUT_DIR) / (Path(img_path).stem + ".json")
    with open(out_path, "w") as f:
        json.dump(template.model_dump(), f, indent=2)

    print(f"[OK] Saved {out_path}")
