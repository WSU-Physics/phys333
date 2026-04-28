import spotipy
from spotipy.oauth2 import SpotifyOAuth
import os
import serial
import time
import pyfirmata
from pyfirmata import Arduino

CLIENT_ID = os.environ.get('CLIENT_ID')
CLIENT_SECRET = os.environ.get('CLIENT_SECRET')
REDIRECT_URI = 'https://www.youtube.com/watch?v=dQw4w9WgXcQ'

sp = spotipy.Spotify(
    auth_manager = SpotifyOAuth(
        client_id = CLIENT_ID,
        client_secret = CLIENT_SECRET,
        redirect_uri = REDIRECT_URI,
        scope = 'user-read-currently-playing'
    )
)

#make this the port arduino is attached to
serialcomm = serial.Serial('COM11', 9600)
serialcomm.timeout = 1


prev_song = ""
current_track = sp.current_user_playing_track()
if current_track is not None:    
    song_name = current_track['item']['name']

serialcomm.write(song_name.encode())
time.sleep(0.5)

while True:
    # current_track = sp.current_user_playing_track()

    if current_track is not None:
        current_track = sp.current_user_playing_track()
        song_name = current_track['item']['name']

    else: 
        print("UH OH! we it's broken - Not playing any music!")


    if prev_song != song_name:
        serialcomm.write(song_name.encode())

        #this is very much needed or no response from the uno
        time.sleep(0.5)

    prev_song = song_name
 
serialcomm.close()

