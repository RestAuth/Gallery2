<div class="gbBlock cgBackground1">
  <h2> {g->text text="RestAuth settings"} </h2>
</div>

{if isset($status.saved)}
  <div class=gbBlock">
    <h2 class="giSuccess"> {g->text text="Settings saved successfully"} </h2>
  </div>
{/if}

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="The URL the RestAuth server listens at (<i>e.g. https://auth.example.com</i>)."}
  </p>
  <label for="cbRestAuthServerInput"> {g->text text="Server:"} </label>
  <input name="{g->formVar var="form[restAuthServer]"}" type="text" value="{$form.restAuthServer}"/>
</div>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="The username that gallery should identify itself with."}
  </p>
  <label for="cbRestAuthUser"> {g->text text="User:"} </label>
  <input name="{g->formVar var="form[restAuthUser]"}" type="text" value="{$form.restAuthUser}"/>
</div>
<div class="gbBlock">
  <p class="giDescription">
    {g->text text="The password that gallery should identify itself with."}
  </p>
  <label for="cbRestAuthPassword"> {g->text text="Password:"} </label>
  <input name="{g->formVar var="form[restAuthPassword]"}" type="password" value="{$form.restAuthPassword}"/>
</div>

<div class="gbBlock">
  <p class="giDescription">
    {g->text text="You can require that a user is in a RestAuth group to be able to log in."}
  </p>
  <label for="cbRestAuthRequireGroup"> {g->text text="Group:"} </label>
  <input name="{g->formVar var="form[restAuthRequireGroup]"}" type="text" value="{$form.restAuthRequireGroup}"/>
</div>

<!--<div class="gbBlock">
  <p class="giDescription">
    {g->text text="Should gallery allow registrations of new users?"}
  </p>
  <label for="cbRestAuthRegistrationInput"> {g->text text="Allow registrations:"} </label>
  <input id="cbRestAuthRegistrationInput" name="{g->formVar var="form[restAuthRegistration]"}" type="checkbox"{if !empty($form.restAuthRegistration)} checked="checked"{/if}/>
</div>
-->
<div class="gbBlock gcBackground1">
  <input class="inputTypeSubmit" name="{g->formVar var="form[action][save]"}" type="submit" value="{g->text text="Save"}"/>
  <input class="inputTypeSubmit" name="{g->formVar var="form[action][reset]"}" type="submit" value="{g->text text="Reset"}"/>
</div>
