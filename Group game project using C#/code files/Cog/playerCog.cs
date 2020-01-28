using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerCog : MonoBehaviour {

    public Canvas deathMenuPopUp; //the deth menu will be placed into this slot so when the player dies it will appear.
    public AudioSource deathSound;//this is the sound that the player makes when they die.
    private List<string> collisions = new List<string>();

    void Start () {

        deathMenuPopUp.enabled = false;
    }


    

    void OnTriggerEnter(Collider col)
    {

        collisions.Add(col.gameObject.name);

        if (collisions.Contains("finHitDetector") && collisions.Contains("killbox"))
            { 
                Destroy(this.gameObject);//destroys the player object.
                deathSound.Play();

                Debug.Log("the player should dead"); // this is for testing only and will need to be removed
                                             // and replaced with the menu popup. 

                deathMenuPopUp.enabled = true;

                //if the player is useing health the damage would be put here.      
             }
    }

    public void OnTriggerExit(Collider col)
    {
        collisions.Remove(col.gameObject.name);
    }
}
