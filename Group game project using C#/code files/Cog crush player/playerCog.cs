using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerCog : MonoBehaviour {

    public Canvas deathMenuPopUp; //the deth menu will be placed into this slot so when the player dies it will appear.
    public AudioSource deathSound;//this is the sound that the player makes when they die.
   private bool isSafe;

    void Start () {

        deathMenuPopUp.enabled = false;
    }

    // Update is called once per frame
    

    void OnCollisionEnter(Collision col)
    {
        

        while (col.gameObject.tag == "killbox")
        {
            isSafe = false;
        }
   
        if (col.gameObject.tag != "killbox")
        {
            isSafe = true;
        }



            if (col.gameObject.tag == "finHitDetector" && col.gameObject.tag == "killbox")
            {

                Destroy(this.gameObject);//destroys the player object.
                deathSound.Play();

                Debug.Log("player is dead"); // this is for testing only and will need to be removed
                                             // and replaced with the menu popup. 

                deathMenuPopUp.enabled = true;


                //if the player is useing health the damage would be put here.          

        }

    }
}
