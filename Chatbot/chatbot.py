import streamlit as st
from thefuzz import process
import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer
import string

# Download NLTK resources (only needed once)
nltk.download('punkt_tab')
nltk.download('stopwords')
nltk.download('wordnet')

# Initialize NLTK components
lemmatizer = WordNetLemmatizer()
stop_words = set(stopwords.words('english'))

keyword_responses = {
    "hello": "Hello! How can I assist you today?",
    "hours": "We are open from 11 AM to 10 PM daily.",
    "reservation": "You can make a reservation online or by calling us.",
    "specials": "Today's special is a vegetarian lasagna.",
    "vegetarian": "We offer several vegetarian dishes like veggie burgers and salads.",
    "gluten-free": "Yes, we have gluten-free options available on our menu.",
    "children's menu": "Yes, we offer a children's menu with kid-friendly meals.",
    "takeout": "Yes, we offer takeout. You can place an order online or call us directly.",
    "payment methods": "We accept major credit cards, debit cards, and cash payments.",
    "parking": "We have a parking lot adjacent to the restaurant for your convenience.",
    "delivery": "We offer delivery services. You can order through our website or delivery apps.",
    "waitlist": "If we're fully booked, we have a waitlist. Would you like to be added?",
    "dress code": "Our dress code is smart casual, but feel free to come as you are!",
    "cancellation policy": "You can cancel your reservation up to 24 hours before your booking.",
    "parties": "We can accommodate large parties. Please make a reservation in advance for groups over 8.",
    "restaurant location": "We are located at 123 Main Street, near the city center.",
    "wifi": "Yes, we offer free Wi-Fi for all customers.",
    "cocktails": "Our bar serves a variety of cocktails, including margaritas, mojitos, and martinis.",
    "events": "We frequently host live music and other events. Check our website for details.",
    "delivery fee": "There is a small delivery fee depending on your location.",
    "open": "We are open every day from 11 AM to 10 PM, including weekends.",
    "reservations required": "It's always best to make a reservation, especially on weekends.",
    "wait time": "Our average wait time is around 15-20 minutes if we are fully booked.",
    "dietary restrictions": "Please let us know if you have any dietary restrictions, and we'll try to accommodate you.",
    "coffee": "We serve a variety of coffee, including espresso, cappuccino, and lattes.",
    "special deals": "We offer various promotions, including discounts on certain days. Check our website for more details.",
    "menu": "Our menu includes pasta, pizza, salads, desserts, and drinks. You can ask for more details on each category.",
}

menu_items = {
    "pasta": ["Alfredo Pasta", "Pesto Pasta", "Arrabbiata Pasta"],
    "pizza": ["Margherita Pizza", "Pepperoni Pizza", "Veggie Delight Pizza"],
    "salads": ["Caesar Salad", "Greek Salad", "Quinoa Salad"],
    "desserts": ["Tiramisu", "Cheesecake", "Chocolate Lava Cake"],
    "drinks": ["Lemonade", "Iced Tea", "Espresso"]
}

# Preprocess text using NLTK
def preprocess_text(text):
    # Tokenize
    tokens = word_tokenize(text.lower())
    # Remove punctuation
    tokens = [word for word in tokens if word not in string.punctuation]
    # Remove stopwords
    tokens = [word for word in tokens if word not in stop_words]
    # Lemmatize
    tokens = [lemmatizer.lemmatize(word) for word in tokens]
    return " ".join(tokens)

# Enhanced get_response function with NLTK
def get_response(user_input, last_topic=None):
    # Preprocess user input
    processed_input = preprocess_text(user_input)
    
    # Handle menu requests
    if ("tell about" in processed_input or "show menu" in processed_input or 
        "details" in processed_input) and last_topic == "menu":
        dishes = []
        for category, items in menu_items.items():
            dishes.append(f"{category.title()}: " + ", ".join(items))
        full_menu = "\n".join(dishes)
        return f"Here's our full menu:\n\n{full_menu}", "menu"
    
    # Check for direct matches with processed input
    for key in keyword_responses:
        if key.replace("'", "") in processed_input:
            return keyword_responses[key], key
    
    # Fall back to fuzzy matching if no direct match
    best_match, match_score = process.extractOne(processed_input, keyword_responses.keys())
    
    if match_score >= 60:
        return keyword_responses[best_match], best_match
    
    return "I'm sorry, I couldn't understand that. Could you please rephrase your question?", None

def chatbot_ui():
    st.title("Restaurant Information Chatbot 🍽")
    st.write("Welcome to our restaurant! Ask me anything about our menu, reservations, specials, or deals.")

    if 'conversation_history' not in st.session_state:
        st.session_state['conversation_history'] = []
    if 'last_topic' not in st.session_state:
        st.session_state['last_topic'] = None
    if 'refresh' not in st.session_state:
        st.session_state['refresh'] = False

    # Text input for the user's message
    user_input = st.text_input("You:", "")

    # If user has entered input
    if user_input:
        response, current_topic = get_response(user_input, st.session_state['last_topic'])
        
        # Append user and bot messages to the session state history
        st.session_state['conversation_history'].append(f"You: {user_input}")
        st.session_state['conversation_history'].append(f"Bot: {response}")
        
        if current_topic:
            st.session_state['last_topic'] = current_topic
        
        # Trigger an update by flipping a session state flag
        st.session_state['refresh'] = not st.session_state['refresh']

    # Display the entire chat history as a non-editable text area
    chat_history = "\n".join(st.session_state['conversation_history'])
    st.text_area("Chat History", value=chat_history, height=300, disabled=True)

if __name__ == "__main__":
    chatbot_ui()



