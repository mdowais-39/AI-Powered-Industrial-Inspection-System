import os
from dotenv import load_dotenv
from google import genai
from google.genai import types  # Import types for configuration
from PIL import Image

# Load environment variables
load_dotenv("project.env")
GEMINI_API = os.getenv("GEMINI_API")

client = genai.Client(api_key=GEMINI_API)

def analyze_image(image_path, prompt):
    img = Image.open(image_path)

    # 1. Define the Google Search tool
    google_search_tool = types.Tool(
        google_search=types.GoogleSearch()
    )

    # 2. Add the tool to the generation configuration
    response = client.models.generate_content(
        model="gemini-3-flash-preview",
        contents=[prompt, img],
        config=types.GenerateContentConfig(
            tools=[google_search_tool]
        )
    )

    return response.text

# Example usage
# result = analyze_image("image.png", "What is happening in this image and search for recent news related to it.")
# print(result)