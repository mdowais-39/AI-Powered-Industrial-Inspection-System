import json

SCHEMA_PATH = "part_semantic_engine/schema.json"


def prompts():
    schema = json.dumps(json.load(open(SCHEMA_PATH)), indent=2)
    user_data = get_user_measurements()

    SYSTEM_PROMPT = """
You are a manufacturing inspection assistant under aerospace quality standards.

RULES:
- Describe only what is visible.
- No manufacturers, models, aircraft, or part numbers.
- User measurements are authoritative.
- Never invent measurements.
- Never add measurements not requested by the user.
- Web search allowed ONLY for missing user-requested measurements.
- Web values must be source="llm", cited, and unverified.
- If not found, mark measurement as unknown.
- Output valid JSON only, strictly following the schema.
"""

    USER_PROMPT = f"""
User measurements:
{user_data}

JSON schema (must match exactly):
{schema}

Instructions:
- Vision-only description.
- Use user measurements as-is.
- For missing requested measurements:
  - Use web search OR mark unknown.
- Do NOT add extra measurements.
- Return JSON only.
"""

    return SYSTEM_PROMPT.strip(), USER_PROMPT.strip()


def get_user_measurements():
    measurements = []
    n = int(input("How many measurements do you want to provide? ").strip())

    for _ in range(n):
        name = input("Measurement name: ").strip()
        value = input("Value (optional): ").strip()
        unit = input("Unit (e.g. mm): ").strip()

        measurements.append({
            "name": name,
            "value": float(value) if value else None,
            "unit": unit or None,
            "source": "user"
        })

    return measurements
