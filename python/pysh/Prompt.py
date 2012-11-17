import os

class Prompt():
    def __init__(self, prompt = os.getenv("PROMPT") or "# "):
        self.prompt = prompt

    def __str__(self):
        return self.prompt
