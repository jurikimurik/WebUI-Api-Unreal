# WebUI API Plugin for Unreal Engine
Created as an AI project for the Polish Japanese Academy of Information Technology by **Yurii Makovskyi**. 🧑‍🎓

That plugin creates communication between the _Unreal Engine_ game and _Text Generation WebUI_ using ***OpenAI API*** extension. ✉️

Highly inspired by [this project](https://github.com/KellanM/OpenAI-Api-Unreal). ⭐

## Installation 🛠️
### WebUI Setup
1. Download and install [Oobabooga’s Text Generation WebUI](https://github.com/oobabooga/text-generation-webui).
2. Download and prepare at least 1 AI model that supports ***text generation***.
Models compatible with "_Transformers_" recommended.

![image](https://github.com/user-attachments/assets/ce080e0f-fe33-4116-8155-61bda3f63a48)

3. Check if it generates everything in _WebUI_ without any problems.

![image](https://github.com/user-attachments/assets/f01f9fb7-a411-4747-9317-e78e48d35238)

### Plugin

1. Download the plugin from [here](https://drive.google.com/file/d/1dTJlGuNuUBXkky67k1tdiQF9CLLRxO4a/view?usp=sharing).
3. Create a `Plugins` folder under your project folder.
4. Copy the plugin there. You should have then similar folder structure as : `YourProject/Plugins/WebUIAPI`.
5. _Rebuild_ the module, if necessary.

### Unreal Engine Project

1. _Clone_ or _download_ [template project here](https://github.com/jurikimurik/WebUI-API-Unreal-Example-Project) (UE 5.4).
2. Extract it and launch “_AiOogaboogaProject.uproject_”.  
There will be a warning that some modules was not found.  
Just press “***Yes***” to rebuild the project.  
3. After building, project should launch and you will be ready to go!


## Introduction Video 📽️
There is a [video on Youtube](https://youtu.be/hSPzyfICNzI) also.

[![API](https://github.com/user-attachments/assets/e94247f5-c917-4e97-8d5d-f833cf484fc3)](https://www.youtube.com/watch?v=hSPzyfICNzI)


## Blueprint Functions 🧰

### Table of Contents
- [Web UI Completion](#web-ui-completion)
- [Web UI Chat Completion](#web-ui-chat-completion)
- [Web UI Stop Generation](#web-ui-stop-generation)
- [Web UI Get Models](#web-ui-get-models)
- [Web UI Load Model](#web-ui-load-model)
- [Web UI Unload Model](#web-ui-unload-model)

### Web UI Completion
This function makes an HTTP request to WebUI for basic completion.

Success: Returns true in “_Success_”, empty “_Error Message_” and filled “_Completion_” structure.
Fail:  Returns false in “_Success_”, text in “_Error Message_” and empty “_Completion_”.

![image](https://github.com/user-attachments/assets/96186f16-b7ba-4b08-a69d-2a62f5c320e3)

### Web UI Chat Completion
Make an HTTP request to WebUI for a chat completion.

Success: Returns true in “_Success_”, empty “_Error Message_” and filled array of “_Message_” structure.
Fail:  Returns false in “_Success_”, text in “_Error Message_” and empty “_Messages_”.

![image](https://github.com/user-attachments/assets/d05fa46e-50aa-4c13-99c4-70cbbf1cfd75)

### Web UI Stop Generation
Make an HTTP request to WebUI to prevent further generation.	

Success: Returns true in “_Success_”, empty “_Error Message_” and text in “_Message_”.
Fail:  Returns false in “_Success_”, text in “_Error Message_” and empty “_Message_”.

![image](https://github.com/user-attachments/assets/2ed22745-0e35-48fe-9637-e890a18a6c16)

### Web UI Get Models
Make an HTTP request to WebUI for retrieving all models that can be loaded.

Success: Returns true in “_Success_”, empty “_Error Message_” and array of texts in “_Message_”.
Fail:  Returns false in “_Success_”, text in “_Error Message_” and empty “_Message_”.

![image](https://github.com/user-attachments/assets/4a0bb746-00ab-4f83-9e83-7200d7306a9f)

### Web UI Load Model
Supported: Transformers Only
Make an HTTP request to WebUI to load desired model.

Success: Returns true in “_Success_”, empty “_Error Message_” and text in “_Message_”.
Fail:  Returns false in “_Success_”, text in “_Error Message_” and empty “_Message_”.

![image](https://github.com/user-attachments/assets/ec6f625d-2cd2-404b-ac1c-14711c536e9d)

### Web UI Unload Model
Make an HTTP request to WebUI for unloading AI model.

Success: Returns true in “_Success_”, empty “_Error Message_” and text in “_Message_”.
Fail:  Returns false in “_Success_”, text in “_Error Message_” and empty “_Message_”.

![image](https://github.com/user-attachments/assets/9fad6452-32f4-4cda-b113-fc9dc986fc45)

## Main Types 🗞️

In every type, ***every parameter*** can be _enabled_ or _disabled_. 
If _enabled_, it will be ***included*** into JSON request.
If _disabled_, it ***won’t*** be included.
Every parameter is <ins>_well-commented_</ins> accordingly to [Oobabooga’s Text Generations WebUI Wiki](https://github.com/oobabooga/text-generation-webui/wiki/03-%E2%80%90-Parameters-Tab).

![image](https://github.com/user-attachments/assets/0dbf4a67-abfd-467b-bcb3-495f230b6ce5)

### Completion Generation Settings
Generation parameters for basic completion. (Retrieved from _FastAPI_ on http://127.0.0.1:5000/docs#/)

![image](https://github.com/user-attachments/assets/95901306-b353-4e14-be6a-b2d6062d6a9a)

### Chat Completion Generation Settings
Generation parameters for chat completions. (Retrieved from _FastAPI_ on http://127.0.0.1:5000/docs#/)

![image](https://github.com/user-attachments/assets/23e054dd-24c6-4c3f-b8fb-86a7b7d91d17)

### Transformer Settings
Setting for transformer type of AI models. (Retrieved from: https://github.com/oobabooga/text-generation-webui/wiki/04-%E2%80%90-Model-Tab)

![image](https://github.com/user-attachments/assets/b9deb00d-7164-4257-80d6-a0628609aba2)



