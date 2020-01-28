using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cog : MonoBehaviour {

    
    public bool TurnLeft = false;
    public bool TurnRight = false;
    public bool isTurning = false;
    [Tooltip("Dont use negative numbers for the speed, the turn right and left will take care of it for you, you can use decimal numbers")]
    public float speed = 0;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {


        if (TurnLeft == true)
        {
            if (isTurning == true)
            {
                transform.Rotate(new Vector3(0, 0, speed), Space.Self);
            }

        }

        if (TurnRight == true)
        {
            if (isTurning == true)
            {
                transform.Rotate(new Vector3(0, 0, -speed), Space.Self);
            }

        }

        if (TurnLeft == true && TurnRight == true)
        {
            TurnLeft = false;
            TurnRight = false;

            Debug.Log("cogs cant turn both ways at once untick one box");

        }
    }
}
