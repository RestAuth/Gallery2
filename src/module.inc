<?php
/*
 * Gallery - a web based photo album viewer and editor
 * Copyright (C) 2000-2007 Bharat Mediratta
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * RestAuth module
 *
 * This module is used to authenticate against RestAuth. Please see the
 * README file for usage/configuration instructions.
 *
 * @package restauth
 * @author Mathias Ertl <mati@fsinf.at>
 * @version $Revision$ $Date: 2006/01/05 07:00:00 $
 */

require_once( "restauth/restauth_users.php" );
require_once( "php-restauth/restauth_common.php" );
 
class RestAuthModule extends GalleryModule {

	function RestAuthModule() {
		global $gallery;

		$this->setId('restauth');
		$this->setName( $gallery->i18n( 'RestAuth' ) );
		$this->setVersion('0.9.0');
		$this->_templateVersion = 1;
		$this->setDescription( $gallery->i18n(
			'Login using RestAuth authentication.' ) );
		$this->setGroup('authentication', $gallery->i18n('Authentication'));
		$this->setCallbacks('getSiteAdminViews');
		$this->setRequiredCoreApi(array(7, 10));
		$this->setRequiredModuleApi(array(3, 0));
	}

	function getSiteAdminViews() {
		return array( null, array( array( 
			'name' => $this->translate( $this->getName() ),
			'view' => 'restauth.RestAuthSiteAdmin' ) ) );
	}

	function performFactoryRegistrations() {
		list ($ret, $params) = $this->fetchParameters();
		if ($ret) {
			return $ret;
		}

		// register event handler
		$ret = GalleryCoreApi::registerFactoryImplementation(
				'GalleryPasswordValidationPlugin', 'RestAuthModule',
				'RestAuthModule', 'modules/restauth/module.inc',
				'restauth',
			null );
		if ($ret) {
			return $ret;
		}
	}

	function performPasswordValidation( $form ) {
		list ($ret, $settings) = GalleryCoreApi::fetchAllPluginParameters('module', 'restauth');
		if ($ret) {
			return array($ret, null, null);
		}

		$error = array();

		$conn = new RestAuthConnection( $settings['restAuthServer'],
			$settings['restAuthUser'], $settings['restAuthPassword'] );
#		$conn = new RestAuthConnection( 'https://auth.fsinf.at',
#			'mati-photos', 'ReiT97Lnh5PUJ7HotrR6emizv1L2xa' );

		$name = $form['username'];
		$pass = $form['password'];
		$restUser = new RestAuthUser( $conn, $name );
		
		$correct = $restUser->verify_password( $pass );
		if ( $correct ) {
			$localUser = new GalleryUser();
			$localUser->create( $name );
			$localUser->save();			
			return array( null, $error, true );
		} else {
			return array( null, $error, false );
		}
	}
}


?>